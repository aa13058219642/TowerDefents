#include "TowerCard.h"

TowerCard::TowerCard()
{
	ID = -1;
	Icon = -1;
	uiName= uiDescription = ActorName = "";
	HP = MP = AP = HP_RegenRate = MP_RegenRate = AP_RegenRate = 0;
	color = Color3B::WHITE;

	for (int i = 0; i < 8; i++)
	{
		spellPosPrice[i] = 0;
	}

	cost = price.money = sell = 0;
}


TowerCard::~TowerCard()
{

}