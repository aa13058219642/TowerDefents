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
	virtual Monster* clone();

	void setMapPath(MapPath path);
	MapPath getMapPath();
	int getDistantToEnd();


	Name icon;
	int price;
	int life;
	Rect hpbar;
	
private:
	MapPath m_path;
	int distantToEnd;

	virtual void onMove(float dt);
	virtual void onBeAttack(int damage, EDamageType damageType);
	virtual void onDead(); 
	virtual void onBindSprite();
	void OnEndPoint();



};

