#pragma once
#include "stdfax.h"
#include "CCostPlayer.h"
class TowerCard
{
public:
	TowerCard();
	~TowerCard();

	int ID;			//所有卡片的ID
	int gid;		//游戏进行时的ID（0-7）
	Name Icon;
	Name uiName;
	Name uiDescription;

	float HP, MP, AP;
	float HP_RegenRate, MP_RegenRate, AP_RegenRate;
	Name ActorName;
	Color3B color;
	float cost;
	CCostPlayer price;
	int spellPosPrice[8];

	vector<Name> weaponName;
	vector<Name> skillName;
};

