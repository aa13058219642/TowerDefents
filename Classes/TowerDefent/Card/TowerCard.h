#pragma once
#include "stdfax.h"
#include "CCostPlayer.h"
class TowerCard
{
public:
	TowerCard();
	~TowerCard();

	int ID;
	int Icon;
	Name uiName;
	Name uiDescription;

	float HP, MP, AP;
	float HP_RegenRate, MP_RegenRate, AP_RegenRate;
	Name ActorName;
	Color3B color;
	float cost;
	CCostPlayer price;
	float sell;
	int spellPosPrice[8];

	vector<Name> weaponName;
	vector<Name> skillName;
};
