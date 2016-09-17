#pragma once
#include "GridPos.h"


class SpellTower
{
public:
	SpellTower(Tower* tower, Direction direction);
	~SpellTower();


private:
	//vector<Upgrade*> m_upgrade;
	Tower* m_tower;
	Direction m_direction;
	Name m_SpellTowerName;
};
