#pragma once
#include "Message.h"



class MessageListener
{
public:
	MessageListener();
	~MessageListener();

	/*消息订阅

	title: 要订阅的消息
	fixedPriority: 接收消息优先级
	*/
	virtual bool msgSubscribe(std::string title, int fixedPriority = 1);
	/*取消订阅*/
	virtual void msgUnsubscribe(std::string title);
	/*取消所有订阅*/
	virtual void msgUnsubscribeAll();
	/*接受消息*/
	virtual void receive(const Message* message) = 0;

protected:
	void rec(cocos2d::EventCustom* event);
	std::vector<std::string> _titles;
	std::vector<cocos2d::EventListenerCustom*> _listener;
};

