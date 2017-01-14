#pragma once
#include "stdfax.h"
#include "CCostPlayer.h"

class SpellCard
{
public:
	SpellCard();
	//SpellCard(Tower* tower, Direction direction);
	~SpellCard();


	int ID;
	Name name;
	int Icon;
	Name behaviorName;
	Name uiName;
	Name uiDescription;
	CCostPlayer costPlayer;
private:

};
