#include "SpellTower.h"
#include "Tower.h"

SpellTower::SpellTower(Tower* tower, Direction direction)
{
	m_tower = tower;
	m_direction = direction;
	m_SpellTowerName = "";
}


SpellTower::~SpellTower()
{

}