#pragma once
#include "stdfax.h"

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
	
	vector<Name> weaponName;
	vector<Name> skillName;
	/*
	HP,MP,AP( RegenRate )
	ActorName,Color
	Cost
	*/

};

