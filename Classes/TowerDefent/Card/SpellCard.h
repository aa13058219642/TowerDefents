#pragma once
#include "stdfax.h"

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
	//CostPlayer
private:

};
