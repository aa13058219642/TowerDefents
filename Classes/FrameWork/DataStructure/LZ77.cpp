#include "LZ77.h"
#include <assert.h>
#include <functional>


#define OFFSET_CODING_LENGTH    (10)
#define MAX_WND_SIZE            1024
#define OFFSET_MASK_CODE        (MAX_WND_SIZE-1)
const ULONG	m = 3;	//Golomb coding's m

LZ77::LZ77()
{

}


LZ77::~LZ77()
{

}

namespace{

void Write1ToBitStream(PUCHAR  pBuffer, ULONG   ulBitOffset)
{
	ULONG   ulByteBoundary;
	ULONG   ulOffsetInByte;

	ulByteBoundary = ulBitOffset >> 3;
	ulOffsetInByte = ulBitOffset & 7;

	*(pBuffer + ulByteBoundary) |= (1 << ulOffsetInByte);
}

void Write0ToBitStream(PUCHAR  pBuffer, ULONG   ulBitOffset)
{
	ULONG   ulByteBoundary;
	ULONG   ulOffsetInByte;

	ulByteBoundary = ulBitOffset >> 3;
	ulOffsetInByte = ulBitOffset & 7;

	*(pBuffer + ulByteBoundary) &= (~(1 << ulOffsetInByte));
}

ULONG ReadBitFromBitStream(PUCHAR  pBuffer, ULONG   ulBitOffset)
{
	ULONG   ulByteBoundary;
	ULONG   ulOffsetInByte;

	ulByteBoundary = ulBitOffset >> 3;
	ulOffsetInByte = ulBitOffset & 7;

	return ((*(PULONG)(pBuffer + ulByteBoundary)) >> ulOffsetInByte) & 1;
}

ULONG WriteGolombCode(ULONG x, PUCHAR pBuffer, ULONG ulBitOffset)
{
	ULONG q, r;
	int i;

	q = (x - 1) >> m;
	r = x - (q << m) - 1;

	for (i = 0; (ULONG)i < q; i++, ulBitOffset++)
	{
		Write1ToBitStream(pBuffer, ulBitOffset);
	}
	Write0ToBitStream(pBuffer, ulBitOffset);
	ulBitOffset++;

	for (i = 0; i < m; i++, ulBitOffset++)
	{
		if ((r >> i) & 1)
		{
			Write1ToBitStream(pBuffer, ulBitOffset);
		}
		else
		{
			Write0ToBitStream(pBuffer, ulBitOffset);
		}
	}

	return m + q + 1;
}

ULONG ReadGolombCode(PULONG pulCodingLength, PUCHAR pBuffer, ULONG ulBitOffset)
{
	ULONG q, r;
	ULONG bit;
	int i;

	for (q = 0;; q++)
	{
		bit = (ULONG)ReadBitFromBitStream(pBuffer, ulBitOffset);
		ulBitOffset++;
		if (!bit)
		{
			break;
		}
	}


	for (i = 0, r = 0; (ULONG)i < m; i++, ulBitOffset++)
	{
		bit = (ULONG)ReadBitFromBitStream(pBuffer, ulBitOffset);
		bit <<= i;
		r |= bit;
	}

	*pulCodingLength = m + q + 1;

	return r + (q << m) + 1;
}

ULONG CompareStrings(PUCHAR string1, PUCHAR string2, ULONG length)
{
	ULONG i;
	PUCHAR p1, p2;

	p1 = string1;
	p2 = string2;

	for (i = 0; i < length; i++)
	{
		if (*p1 == *p2)
		{
			p1++;
			p2++;
		}
		else
		{
			break;
		}
	}

	return p1 - string1;
}

void FindLongestSubstring(PUCHAR pSourceString, PUCHAR pString, ULONG ulSourceStringLength, PULONG pulSubstringOffset, PULONG pulSubstringLength)
{
	PUCHAR pSrc;
	ULONG  offset, length;
	ULONG  ulMaxLength;


	*pulSubstringOffset = offset = 0;
	*pulSubstringLength = 0;

	if (nullptr == pSourceString || nullptr == pString)
	{
		return;
	}

	ulMaxLength = ulSourceStringLength;
	pSrc = pSourceString;

	while (ulMaxLength > 0)
	{
		length = CompareStrings(pSrc, pString, ulMaxLength);

		if (length > *pulSubstringLength)
		{
			*pulSubstringLength = length;
			*pulSubstringOffset = offset;
		}

		pSrc++;
		offset++;
		ulMaxLength--;
	}
}

void WriteBits(PUCHAR pDataBuffer, ULONG ulOffsetToWrite, ULONG ulBits, ULONG ulBitLength)
{
	ULONG ulDwordsOffset;
	ULONG ulBitsOffset, ulBitsRemained;

	ulDwordsOffset = ulOffsetToWrite >> 5;
	ulBitsOffset = ulOffsetToWrite & 31;
	ulBitsRemained = 32 - ulBitsOffset;

	if (0 == ulBitsOffset)
	{
		*((PULONG)pDataBuffer + ulDwordsOffset) = ulBits;
	}
	else if (ulBitsRemained >= ulBitLength)
	{
		*((PULONG)pDataBuffer + ulDwordsOffset) |= (ulBits << ulBitsOffset);
	}
	else
	{
		*((PULONG)pDataBuffer + ulDwordsOffset) |= (ulBits << ulBitsOffset);
		*((PULONG)pDataBuffer + ulDwordsOffset + 1) = ulBits >> ulBitsRemained;
	}
}

void ReadBits(PUCHAR pDataBuffer, ULONG ulOffsetToRead, PULONG pulBits)
{
	ULONG ulDwordsOffset;
	ULONG ulBitsOffset, ulBitsLength;

	ulDwordsOffset = ulOffsetToRead >> 5;
	ulBitsOffset = ulOffsetToRead & 31;
	ulBitsLength = 32 - ulBitsOffset;


	*pulBits = *((PULONG)pDataBuffer + ulDwordsOffset);
	if (0 != ulBitsOffset)
	{
		(*pulBits) >>= ulBitsOffset;
		(*pulBits) |= (*((PULONG)pDataBuffer + ulDwordsOffset + 1)) << ulBitsLength;
	}
}

}

int LZ77::Compress(const PUCHAR pDataBuffer, ULONG ulDataLength, PUCHAR pOutputBuffer, PULONG pulNumberOfBits)
{
	LONG        iSlideWindowPtr;
	ULONG       ulBytesCoded;
	ULONG       ulMaxlength;
	PUCHAR      pSlideWindowPtr;
	PUCHAR      pUnprocessedDataPtr;

	ULONG   offset;
	ULONG   length;
	ULONG   ulCodingLength;

	ULONG   ulBitOffset;
	UCHAR   cc;

	int     i;

	iSlideWindowPtr = -MAX_WND_SIZE;
	pSlideWindowPtr = nullptr;
	ulBitOffset = 0;
	ulBytesCoded = 0;

	while (ulBytesCoded < ulDataLength)
	{
		if (iSlideWindowPtr >= 0)
		{
			pSlideWindowPtr = pDataBuffer + iSlideWindowPtr;
			ulMaxlength = MAX_WND_SIZE;

		}
		else if (iSlideWindowPtr >= -MAX_WND_SIZE)
		{
			pSlideWindowPtr = pDataBuffer;
			ulMaxlength = MAX_WND_SIZE + iSlideWindowPtr;
		}
		else
		{
			pSlideWindowPtr = nullptr;
			ulMaxlength = 0;
		}

		pUnprocessedDataPtr = pDataBuffer + ulBytesCoded;
		if (ulMaxlength > ulDataLength - ulBytesCoded)
		{
			ulMaxlength = ulDataLength - ulBytesCoded;
		}

		FindLongestSubstring(
			pSlideWindowPtr,
			pUnprocessedDataPtr,
			ulMaxlength,
			&offset,
			&length
			);

		assert(length <= MAX_WND_SIZE);
		assert(offset < MAX_WND_SIZE);

		if (length > 1)
		{

			Write1ToBitStream(pOutputBuffer, ulBitOffset);
			ulBitOffset++;

			for (i = 0; i < OFFSET_CODING_LENGTH; i++, ulBitOffset++)
			{
				if ((offset >> i) & 1)
				{
					Write1ToBitStream(pOutputBuffer, ulBitOffset);
				}
				else
				{
					Write0ToBitStream(pOutputBuffer, ulBitOffset);
				}
			}

			ulCodingLength = WriteGolombCode(length, pOutputBuffer, ulBitOffset);

			ulBitOffset += ulCodingLength;
			iSlideWindowPtr += length;
			ulBytesCoded += length;

		}
		else
		{
			Write0ToBitStream(pOutputBuffer, ulBitOffset);
			ulBitOffset++;

			cc = (*pUnprocessedDataPtr);
			for (i = 0; i < 8; i++, ulBitOffset++)
			{
				if ((cc >> i) & 1)
				{
					Write1ToBitStream(pOutputBuffer, ulBitOffset);
				}
				else
				{
					Write0ToBitStream(pOutputBuffer, ulBitOffset);
				}
			}

			iSlideWindowPtr++;
			ulBytesCoded++;
		}

	}

	if (ulBytesCoded != ulDataLength)
	{
		assert(ulBytesCoded == ulDataLength);
	}

	*pulNumberOfBits = ulBitOffset;

	return ceil(ulBitOffset / 8.0);
}

int LZ77::Compress(const char* pDataBuffer, int ulDataLength, OUT char* pOutputBuffer, OUT int& pulNumberOfBits)
{
	return Compress((PUCHAR)pDataBuffer, (ULONG)ulDataLength, (PUCHAR)pOutputBuffer, (PULONG)&pulNumberOfBits);
}

int LZ77::Decompress(const PUCHAR pDataBuffer, ULONG  ulNumberOfBits, PUCHAR pOutputBuffer, PULONG pulNumberOfBytes)
{
	LONG        iSlideWindowPtr;
	PUCHAR      pSlideWindowPtr;

	ULONG   length, offset;
	ULONG   bit;
	UCHAR   cc;
	int     i;

	ULONG   ulBytesDecoded;
	ULONG   ulBitOffset;

	ULONG   ulCodingLength;
	PUCHAR  pWrite;

	iSlideWindowPtr = -MAX_WND_SIZE;
	pWrite = (PUCHAR)pOutputBuffer;
	ulBitOffset = 0;
	ulBytesDecoded = 0;


	while (ulBitOffset < ulNumberOfBits)
	{
		bit = ReadBitFromBitStream(pDataBuffer, ulBitOffset);
		ulBitOffset++;

		if (bit)
		{
			if (iSlideWindowPtr >= 0)
			{
				pSlideWindowPtr = pOutputBuffer + iSlideWindowPtr;

			}
			else if (iSlideWindowPtr >= -MAX_WND_SIZE)
			{
				pSlideWindowPtr = pOutputBuffer;
			}
			else
			{
				pSlideWindowPtr = nullptr;
			}


			for (i = 0, offset = 0; i < OFFSET_CODING_LENGTH; i++, ulBitOffset++)
			{
				bit = ReadBitFromBitStream(pDataBuffer, ulBitOffset);
				offset |= (bit << i);
			}

			length = ReadGolombCode(&ulCodingLength, pDataBuffer, ulBitOffset);

			assert(offset < MAX_WND_SIZE);

			if (length > MAX_WND_SIZE)
			{
				assert(length <= MAX_WND_SIZE);
			}
			ulBitOffset += ulCodingLength;

			memmove(pWrite, pSlideWindowPtr + offset, length);
			pWrite += length;
			iSlideWindowPtr += length;
			ulBytesDecoded += length;
		}
		else
		{
			for (i = 0, cc = 0; i < 8; i++, ulBitOffset++)
			{
				bit = ReadBitFromBitStream(pDataBuffer, ulBitOffset);
				cc |= ((UCHAR)bit << i);
			}

			*pWrite++ = cc;
			iSlideWindowPtr++;
			ulBytesDecoded++;
		}

	}

	*pulNumberOfBytes = ulBytesDecoded;
	return ceil(ulBytesDecoded / 8.0);
}

int LZ77::Decompress(const char* pDataBuffer, int  ulNumberOfBits, OUT char* pOutputBuffer, OUT int& pulNumberOfBytes)
{
	return Decompress((PUCHAR)pDataBuffer, (ULONG)ulNumberOfBits, (PUCHAR)pOutputBuffer, (PULONG)&pulNumberOfBytes);
}











