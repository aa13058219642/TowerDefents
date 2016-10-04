#include "TowerCard.h"

TowerCard::TowerCard()
{
	ID = -1;
	Icon = -1;
	uiName= uiDescription = ActorName = "";
	HP = MP = AP = HP_RegenRate = MP_RegenRate = AP_RegenRate = 0;
	color = Color3B::WHITE;
}


TowerCard::~TowerCard()
{

}