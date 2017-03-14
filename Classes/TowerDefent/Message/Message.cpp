#include "Message.h"

Message::Message()
{
	keyword = "";
	valueMap.clear();
}

Message::Message(std::string keyword)
{
	this->keyword = keyword;
	valueMap.clear();
}


Message::~Message()
{

}

void Message::post(std::string title, Message* message)
{
	//在这报错很大可能是 接受函数receive()内的代码报错
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(title, message);
}

void Message::post(std::string title)
{
	//在这报错很大可能是 接受函数receive()内的代码报错
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(title, this);
}

