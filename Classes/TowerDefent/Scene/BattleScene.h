#pragma once
#include "stdfax.h"

#include "UnitLayer.h"
#include "TowerSelectLayer.h"
#include "GameMapLayer.h"
#include "TowerInfoLayer.h"
#include "GameMapInfoLayer.h"
#include "GameInfoLayer.h"

class BattleScene : public cocos2d::Scene
{
public:

	BattleScene();
	~BattleScene();

	//CREATE_FUNC(BattleScene);
	static BattleScene* create(int wrold, int level);
	virtual bool init(int wrold, int level);
	virtual void update(float dt);


	DrawNode* drawNode;

	Layer* lay;
private:
	UnitLayer* unitLayer;
	TowerSelectLayer* towerSelectLayer;
	GameMapLayer* gameMapLayer;
	TowerInfoLayer* towerInfoLayer;
	GameMapInfoLayer* gameMapInfoLayer;
	GameInfoLayer* gameInfoLayer;
};
