#pragma once
#include "stdfax.h"

#include "UnitLayer.h"
#include "TowerSelectLayer.h"
#include "GameMapLayer.h"
#include "TowerInfoLayer.h"
#include "GameInfoLayer.h"
#include "LevelFinishLayer.h"

class BattleScene : public cocos2d::Scene
{
public:

	BattleScene();
	~BattleScene();

	//CREATE_FUNC(BattleScene);
	static BattleScene* create();
	virtual bool init();
	virtual void update(float dt);
	virtual void onExit();


	DrawNode* drawNode;

	Layer* lay;
private:
	UnitLayer* unitLayer;
	TowerSelectLayer* towerSelectLayer;
	GameMapLayer* gameMapLayer;
	TowerInfoLayer* towerInfoLayer;
	GameInfoLayer* gameInfoLayer;
	LevelFinishLayer* LevelFinishLayer;
};
