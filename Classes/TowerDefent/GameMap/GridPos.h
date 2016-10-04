#pragma once
#include "stdfax.h"
#include "SpellCard.h"
#include "TowerCard.h"

enum EGridPosType{
	GridPosType_Empty,
	GridPosType_Tower,
	GridPosType_SpellEmpty,
	GridPosType_SpellTower
};

enum Direction{ North, NorthWest, West, SouthWest, South, SouthEast, East, NorthEast, Center };


class Tower;

class GridPos
{
public:
	int ID;

	GridPos();
	GridPos(int id, Rect rect);

	~GridPos();

	void onClick();
	EGridPosType getType();
	const Rect& getRect();
	Point getPos();
	Tower* getTower();

	void setAroundGridPosID(const int* around);
	void setAroundGridPosID(Direction dir, int id);
	const int* getAroundGridPosID();
	int getAroundGridPosID(Direction dir);

	void initTower();
	
	void buildTower(const TowerCard* towerCard);
	void buildSpellPos(Tower* parent, Direction dirRelativeToTower);
	void buildSpellTower(const SpellCard* spellTower);

	void drawMyOutLine(DrawNode* drawNode);
private: 
	EGridPosType m_type;
	Tower* m_tower;
	Rect m_rect;
	Point m_pos;
	Direction m_dir;
	int m_around[8];
};

