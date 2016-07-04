#pragma once
#include "stdfax.h"
#include "GameObject.h"
#include "GameMap.h"
class MonsterBase : public GameObject
{
public:
	MonsterBase();
	~MonsterBase();

	static MonsterBase* create(int MonsterID, MapPath path, bool isDebug = false);
	bool init(int MonsterID, MapPath path, bool isDebug = false);
	virtual void drawMyOutLine(DrawNode* drawNode);
	virtual void update(float dt);

	int type;
	CC_SYNTHESIZE(MapPath, m_path, MovePath);
	//int m_speed;

private:
	virtual void onMove(float dt);
	virtual void onBeAttack(int damage);
	virtual void onDead(); 
	void OnEndPoint();
};

