#include "UserData.h"
#include "cocos2d.h"
#include "stdfax.h"
#include "json\stringbuffer.h"
#include "json\writer.h"
#include "LZ77.h"

USING_NS_CC;
using namespace std;

UserData* UserData::p_myinstance = nullptr;

struct DataSize
{
	int FileSize;	//dat文件中压缩包数据的字节大小
	int SourceSize;	//压缩包数据压缩前(解包后)的大小
	int bitSize;	//压缩包数据压缩后的位大小
	char* lz77data;
};

union FileData
{
	struct{
		int FileSize;	//dat文件中压缩包数据的字节大小
		int SourceSize;	//压缩包数据压缩前(解包后)的大小
		int bitSize;	//压缩包数据压缩后的位大小
	}datasize;

	struct{
	private:
		char ch[12];
	public:
		char* lz77data;
	}dat;
	char* data;
};




UserData::UserData()
{
	doc = nullptr;
}


UserData::~UserData()
{

}

UserData* UserData::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new UserData();
	}
	return p_myinstance;
}

int UserData::getInt(std::string keyname)
{
	CCASSERT(doc.HasMember(keyname.c_str()), "keyname NOT found !");
	return doc[keyname.c_str()].GetInt();
}

double UserData::getDouble(std::string keyname)
{
	CCASSERT(doc.HasMember(keyname.c_str()), "keyname NOT found !");
	return doc[keyname.c_str()].GetDouble();
}

std::string UserData::getString(std::string keyname)
{
	CCASSERT(doc.HasMember(keyname.c_str()), "keyname NOT found !");
	return doc[keyname.c_str()].GetString();
}

std::string UserData::getJsonString(std::string keyname)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc[keyname.c_str()].Accept(writer);
	return buffer.GetString();
}


void UserData::setValue(std::string keyname, int value)
{
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	if (doc.HasMember(keyname.c_str()))
	{
		doc[keyname.c_str()] = value;
	}
	else
	{
		doc.AddMember(rapidjson::Value(keyname.c_str(), allocator), value, allocator);
	}
}

void UserData::setValue(std::string keyname, double value)
{
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	if (doc.HasMember(keyname.c_str()))
	{
		doc[keyname.c_str()] = value;
	}
	else
	{

		doc.AddMember(rapidjson::Value(keyname.c_str(), allocator), value, allocator);
	}
}

void UserData::setValue(std::string keyname, std::string value)
{
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	if (doc.HasMember(keyname.c_str()))
	{
		doc[keyname.c_str()] = rapidjson::Value(value.c_str(), allocator);
	}
	else
	{
		doc.AddMember(rapidjson::Value(keyname.c_str(), allocator), rapidjson::Value(value.c_str(), allocator), allocator);
	}
}


void UserData::Load(std::string filename, bool useLz77)
{
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile(fin->getWritablePath() + filename);
	if (!data.isNull())
	{
		if (useLz77)
		{
			FileData* filedata = (FileData*)data.getBytes();

			char* buf = new char[filedata->datasize.SourceSize];
			
			LZ77::Decompress((char*)&filedata->dat.lz77data, filedata->datasize.bitSize, buf, filedata->datasize.SourceSize);

			std::string str = string(buf, filedata->datasize.SourceSize);
			doc.Parse<0>(str.c_str());

			delete buf;
		}
		else
		{
			std::string str = string((char*)data.getBytes(), data.getSize());
			doc.Parse<0>(str.c_str());
		}
	}
	else
	{
		doc.Parse("{}");
	}
}

void UserData::Save(std::string filename, bool useLz77)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	string jsonstr = buffer.GetString();

	if (useLz77)
	{
		char* buf = new char[jsonstr.length() + sizeof(int) * 3];
		FileData* filedata = (FileData*)buf;
		filedata->datasize.SourceSize = jsonstr.length();
		filedata->datasize.FileSize = LZ77::Compress(jsonstr.c_str(), filedata->datasize.SourceSize, (char*)&filedata->dat.lz77data, filedata->datasize.bitSize);

		Data dat;
		dat.fastSet((PUCHAR)buf, ssize_t(sizeof(int) * 3 + filedata->datasize.FileSize));
		 
		FileUtils* fin = FileUtils::getInstance();
		std::string path = FileUtils::getInstance()->getWritablePath();
		FileUtils::getInstance()->writeDataToFile(dat, path + filename);

		dat.fastSet(nullptr, 0);


		delete buf;
	}
	else
	{
		Data dat;
		dat.fastSet((PUCHAR)jsonstr.c_str(), jsonstr.size());

		FileUtils* fin = FileUtils::getInstance();
		std::string path = FileUtils::getInstance()->getWritablePath();
		FileUtils::getInstance()->writeDataToFile(dat, path + filename);

		dat.fastSet(nullptr,0);
	}
}




