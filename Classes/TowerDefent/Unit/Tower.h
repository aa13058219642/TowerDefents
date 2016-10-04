#pragma once
#include "stdfax.h"
#include "Unit.h"
#include "GridPos.h" 
#include "SpellCard.h"
#include "TowerCard.h"

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

	void buildTower(const TowerCard* towerCard);
	void buildSpellTowerPos(Direction direction);
	void buildSpellTower(Direction direction, const SpellCard* spellTower);
	void sellSpellTower(Direction direction);
	void sellTower();

	Color3B getColor();
	const TowerCard* getTowerCard();
private:
	GridPos* m_gridPos;
	Color3B m_color;
	//vector<SpellTower*> m_SpellTower;
	SpellCard* m_SpellTower[8];
	const TowerCard* m_TowerCard;

	virtual void onAttack(Unit* target);
	virtual void onBindSprite();

};

