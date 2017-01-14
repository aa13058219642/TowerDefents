#include "MessageListener.h"

using namespace cocos2d;

MessageListener::MessageListener()
{

}


MessageListener::~MessageListener()
{
	msgUnsubscribeAll();
}


bool MessageListener::msgSubscribe(std::string title, int fixedPriority)
{
	EventListenerCustom* customEvt = EventListenerCustom::create(title, CC_CALLBACK_1( MessageListener::rec,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(customEvt, fixedPriority);
	_titles.push_back(title);
	_listener.push_back(customEvt);
	return true;
}

void MessageListener::msgUnsubscribe(std::string title)
{
	int id = -1;
	int size = _titles.size();
	for (int i = 0; i < size; i++)
	{
		if (_titles[i] == title)
		{
			id = i;
			break;
		}
	}

	if (id != -1)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_listener[id]);
		
		_listener.erase(_listener.begin() + id);
		_titles.erase(_titles.begin() + id);
	}
}

void MessageListener::msgUnsubscribeAll()
{
	for (auto listener : _listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}

	_titles.clear();
	_listener.clear();
}




void MessageListener::rec(EventCustom* event)
{
	(event->getUserData() == nullptr) ?
		this->receive(nullptr) :
		this->receive(static_cast<Message*>(event->getUserData()));
}












