#pragma once
#include "stdfax.h"
#include "CUnit.h"
#include "GridPos.h" 
#include "SpellCard.h"
#include "TowerCard.h"

class Tower : public CUnit
{
public:
	//Tower();
	Tower(GridPos* GridPos);
	~Tower();

	/*»æÖÆÂÖÀª*/
	virtual void drawMyOutLine(DrawNode* drawNode);
	
	virtual void update(float dt);
	virtual void onClick();

	void buildTower(const TowerCard towerCard);
	void buildSpellTowerPos(Direction direction);
	void buildSpellTower(Direction direction, const SpellCard spellTower);

	void sellTower();
	void sellSpellPos(Direction direction);
	void sellSpellTower(Direction direction);

	Color3B getColor();
	TowerCard getTowerCard();
	const SpellCard* getSpellCard(Direction direction);
	int getSpellPosCount();

	float getSumPrice();
	float getSellPrice();
	float getSellSpellPosPrice(Direction direction);
private:
	GridPos* m_gridPos;
	Color3B m_color;
	//vector<SpellTower*> m_SpellTower;
	SpellCard* m_SpellTower[8];
	TowerCard m_TowerCard;
	int spellPosCount;


	virtual void onAttack(CUnit* target);
	virtual void onBindSprite();

};

