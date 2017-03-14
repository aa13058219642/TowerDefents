#pragma once
#include "stdfax.h"
#include "CUnit.h"
#include "GameMap.h"
class Monster : public CUnit
{
public:
	//Monster(int MonsterID, MapPath path);
	Monster();
	~Monster();

	//static Monster* create(int MonsterID, MapPath path);
	//bool init(int MonsterID, MapPath path);
	virtual void drawMyOutLine(DrawNode* drawNode);
	virtual void update(float dt);

	void setMapPath(MapPath path);
	MapPath getMapPath();

	virtual Monster* clone();

	Name icon;
	int price;
	int life;
private:
	MapPath m_path;

	virtual void onMove(float dt);
	virtual void onBeAttack(int damage, EDamageType damageType);
	virtual void onDead(); 
	virtual void onBindSprite();
	void OnEndPoint();
};

