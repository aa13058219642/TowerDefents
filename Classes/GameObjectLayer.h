#pragma once
#include "stdfax.h"
#include "GameMap.h"
#include "GameObject.h"
#include "TowerBase.h"


class GameObjectLayer : public Layer
{
public:
	GameObjectLayer();

	static GameObjectLayer* create(bool isDebug = false);
	bool init(bool isDebug = false);
	
	void addGameObject(GameObject* child);
	void removeGameObject(GameObject* child);

	virtual void update(float dt);
	GameObject* findGameObject(Point pos, GameObjectType type);

	int curWave;
	int curWaveMonster;
	vector<Wave> WaveList;
	Vector<GameObject*> gameObjectList;

	DrawNode* debugDrawNode;
	Label* debugLabel;
private:
	bool isDebug;

	void CreateWave();
	void CreateMonster();
	void RunDelayAction(SEL_CallFunc selector, float delayTime);

	void DebugDraw();
};



