#pragma once
#include <string>

#include "json\stringbuffer.h"
#include "json\writer.h"
#include "json\rapidjson.h"
#include "json\document.h"

#define DEFAULT_USERDATA_FILE "userdata.dat"

class UserData
{
public:
	~UserData();
	static UserData* getInstance();

	int getInt(std::string keyname);
	double getDouble(std::string keyname);
	std::string getString(std::string keyname);
	std::string getJsonString(std::string keyname);

	void setValue(std::string keyname, int value);
	void setValue(std::string keyname, double value);
	void setValue(std::string keyname, std::string value);

	void Load(std::string filename = DEFAULT_USERDATA_FILE, bool useLz77 = true);
	void Save(std::string filename = DEFAULT_USERDATA_FILE, bool useLz77 = true);


private:
	UserData();
	static UserData* p_myinstance;
	rapidjson::Document doc;
};

