#pragma once
#include "stdfax.h"
#include "Unit.h"
#include "GameMap.h"
class Monster : public Unit
{
public:
	//Monster();
	Monster(int MonsterID, MapPath path);
	~Monster();

	//static Monster* create(int MonsterID, MapPath path);
	//bool init(int MonsterID, MapPath path);
	virtual void drawMyOutLine(DrawNode* drawNode);
	virtual void update(float dt);

	CC_SYNTHESIZE(MapPath, m_path, MovePath);


private:
	virtual void onMove(float dt);
	virtual void onBeAttack(int damage, EDamageType damageType);
	virtual void onDead(); 
	virtual void onBindSprite();
	void OnEndPoint();
};

