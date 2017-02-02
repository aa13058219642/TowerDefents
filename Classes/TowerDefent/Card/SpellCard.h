#pragma once
#include "stdfax.h"
#include "CCostPlayer.h"

class SpellCard
{
public:
	SpellCard();
	//SpellCard(Tower* tower, Direction direction);
	~SpellCard();


	int ID;			//所有卡片的ID
	int gid;		//游戏进行时的ID（0-7）
	Name name;
	int Icon;
	Name behaviorName;
	Name uiName;
	Name uiDescription;
	CCostPlayer costPlayer;

	float cost;
	CCostPlayer price;

private:

};
