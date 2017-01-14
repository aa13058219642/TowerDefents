#include "Player.h"
#include "TowerDefentShare.h"

Player* Player::p_myinstance = nullptr;

Player* Player::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new Player();
	}
	return p_myinstance;
}



Player::Player()
{
	money = 0;
	life = 0;
	score = 0;
	sumDamage = 0;
	msgSubscribe(Message_Player);

}

Player::~Player()
{

}

void Player::reset()
{
	money = 0;
	life = 20;
	score = 0;
	sumDamage = 0;
}

float Player::getMoney()
{
	return money;
}

void Player::setMoney(float money)
{
	this->money = money;

	Message msg(Message_Global);
	msg.keyword = "updateMoney";
	msg.post(Message_Global);

}


int Player::getLife()
{
	return life;
}

void Player::setLife(int life)
{
	this->life = life;
}


void Player::receive(const Message* message)
{
	if (message->keyword == "Money")
	{
		this->setMoney(this->getMoney() + message->valueMap.at("value").asFloat());
	}
}
