#pragma once
//#include "stdfax.h"
#include "cocos2d.h"



class Message
{
public:
	Message();
	Message(std::string keyword);
	~Message();
	static void post(std::string title, Message* message);

	void post(std::string title);

	std::string keyword;
	cocos2d::ValueMap valueMap;
	 

};

