#pragma once

#define OUT 

typedef long LONG;
typedef unsigned long ULONG;
typedef ULONG *PULONG;

typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

class LZ77
{
public:
	LZ77();
	~LZ77();

	static int Compress(const PUCHAR pDataBuffer, ULONG ulDataLength, OUT PUCHAR pOutputBuffer, OUT PULONG pulNumberOfBits);
	static int Compress(const char* pDataBuffer, int ulDataLength, OUT char* pOutputBuffer, OUT int& pulNumberOfBits);

	static int Decompress(const PUCHAR pDataBuffer, ULONG ulNumberOfBits, OUT PUCHAR pOutputBuffer, OUT PULONG pulNumberOfBytes);
	static int Decompress(const char* pDataBuffer, int ulNumberOfBits, OUT char* pOutputBuffer, OUT int& pulNumberOfBytes);
};

