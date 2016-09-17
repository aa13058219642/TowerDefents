#pragma once
#include "stdfax.h"
#include "Unit.h"
#include "GridPos.h" 
#include "SpellTower.h"

class Tower : public Unit
{
public:
	//Tower();
	Tower(GridPos* GridPos);
	~Tower();

	/*»æÖÆÂÖÀª*/
	virtual void drawMyOutLine(DrawNode* drawNode);
	
	virtual void update(float dt);
	virtual void onClick();

	void buildTower(int tid);
	void buildUpgradPos(Direction direction);
	void buildSpellTower(Direction direction, int SpellTowerID);
	void sellSpellTower(Direction direction);
	void sellTower();

	Color3B getColor();

private:
	GridPos* m_gridPos;
	Color3B m_color;
	vector<SpellTower*> m_SpellTower;

	virtual void onAttack(Unit* target);
	virtual void onBindSprite();

};

