#pragma once
#include "stdfax.h"
#include "GameMap.h"
#include "TowerBase.h"
#include "MonsterBase.h"
#include "Bullet.h"

class GameObjectLayer : public Layer
{
public:
	GameObjectLayer();

	static GameObjectLayer* create(bool isDebug = false);
	bool init(bool isDebug = false);
	


	virtual void update(float dt);
	TowerBase* findTower(Point pos);

	int curWave;
	int curWaveMonster;
	Vector<MonsterBase*> monsterList;
	Vector<TowerBase*> towerList;
	Vector<Bullet*> bulletList;
	vector<Wave> WaveList;

	DrawNode* debugDrawNode;
	Label* debugLabel;
private:
	bool isDebug;

	void CreateWave();
	void CreateMonster();
	void RunDelayAction(SEL_CallFunc selector, float delayTime);

	void DebugDraw();
};



