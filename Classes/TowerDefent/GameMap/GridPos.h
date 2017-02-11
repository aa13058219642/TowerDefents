#pragma once
#include "stdfax.h"
#include "SpellCard.h"
#include "TowerCard.h"
#include "CActor.h"

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

	bool isClickMe(Point pos);
	void onClick();
	EGridPosType getType();
	const Rect& getRect();
	Point getPos();
	Tower* getTower();
	float getSellPrice();
	Direction getDirection();
	void sell();
	void reset();

	void setAroundGridPosID(const int* around);
	void setAroundGridPosID(Direction dir, int id);
	const int* getAroundGridPosID();
	int getAroundGridPosID(Direction dir);

	void bindActor();
	
	void buildTower(const TowerCard towerCard);
	void buildSpellPos(Tower* parent, Direction dirRelativeToTower);
	void buildSpellTower(const SpellCard spellTower);

	void drawMyOutLine(DrawNode* drawNode);
private: 
	EGridPosType m_type;
	CActor* m_actor;
	Tower* m_tower;
	Tower* m_parent;
	Rect m_rect;
	Point m_pos;
	Direction m_dir;
	int m_around[8];
};

