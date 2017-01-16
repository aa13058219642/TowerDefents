#pragma once
#include "stdfax.h"
#include "TowerCard.h"
#include "SpellCard.h"
#include "Message\MessageListener.h"

class Player : public CPlayer, MessageListener
{
public:
	static Player* getInstance();
	~Player();

	void reset();

	void addMoney(float money);
	void setMoney(float money);
	float getMoney();

	int getLife();
	void setLife(int life);

	virtual void receive(const Message* message);

	void setTowerCard(std::vector<TowerCard> towerCard);
	std::vector<TowerCard> getTowerCard();
	
	void setSpellCard(std::vector<SpellCard> spellCard);
	std::vector<SpellCard> getSpellCard();

	void addTowerPrice(int id, float money);
	void addSpellPrice(int id, float money);

private:
	Player();
	static Player* p_myinstance;


	float money;
	int life;
	int score;
	int sumDamage;
	std::vector<TowerCard> m_TowerCard;
	std::vector<SpellCard> m_SpellCard;
	EventDispatcher* _eventDispatcher;
};

