#include "SpellCard.h"
#include "Tower.h"




//SpellCard::SpellCard(Tower* tower, Direction direction)
//{
//	m_tower = tower;
//	m_direction = direction;
//	m_SpellTowerName = "";
//}

SpellCard::SpellCard()
{
	ID = -1;
	name = "";
	Icon = -1;
	behaviorName = "";
	uiName = "";
	uiDescription = "";
}


SpellCard::~SpellCard()
{

}