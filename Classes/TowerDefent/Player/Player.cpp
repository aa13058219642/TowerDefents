#include "Player.h"
#include "TowerDefentShare.h"
#include "TowerCardManager.h"
#include "SpellCardManager.h"

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
	m_SpellCard.resize(8);
	m_TowerCard.resize(8);
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

void Player::addMoney(float money)
{
	setMoney(this->money + money);
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



void Player::setTowerCard(std::vector<TowerCard> towerCard)
{
	m_TowerCard.clear();
	for (auto t : towerCard)
	{
		m_TowerCard.push_back(t);
	}
}

std::vector<TowerCard> Player::getTowerCard()
{
	return m_TowerCard;
}

void Player::setSpellCard(std::vector<SpellCard> spellCard)
{
	m_SpellCard.clear();
	for (auto t : spellCard)
	{
		m_SpellCard.push_back(t);
	}
}

std::vector<SpellCard> Player::getSpellCard()
{
	return m_SpellCard;
}

void Player::addTowerPrice(int id, float money)
{
	m_TowerCard[id].price.money += money;
}

void Player::addSpellPrice(int id, float money)
{
	m_SpellCard[id].price.money += money;
}











