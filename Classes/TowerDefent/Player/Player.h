#pragma once
#include "stdfax.h"
#include "Message\MessageListener.h"

class Player : public CPlayer, MessageListener
{
public:
	static Player* getInstance();
	~Player();

	void reset();

	float getMoney();
	void setMoney(float money);

	int getLife();
	void setLife(int life);

	virtual void receive(const Message* message);

private:
	Player();
	static Player* p_myinstance;


	float money;
	int life;
	int score;
	int sumDamage;

	EventDispatcher* _eventDispatcher;
};

