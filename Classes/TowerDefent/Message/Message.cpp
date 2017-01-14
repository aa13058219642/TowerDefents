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
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(title, message);
}

void Message::post(std::string title)
{
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(title, this);
}

