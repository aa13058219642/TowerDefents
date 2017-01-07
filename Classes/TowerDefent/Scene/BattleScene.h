#pragma once
#include "stdfax.h"

#include "UnitLayer.h"
#include "TowerSelectLayer.h"
#include "GameMapLayer.h"
#include "TowerInfoLayer.h"
#include "GameMapInfoLayer.h"

class BattleScene : public Layer
{
public:

	BattleScene();
	~BattleScene();

	//CREATE_FUNC(BattleScene);
	static Scene* createScene(int level);
	static BattleScene* create(int level);
	virtual bool init(int level);
	virtual void update(float dt);


	DrawNode* drawNode;

	Layer* lay;
private:
	UnitLayer* unitLayer;
	TowerSelectLayer* towerSelectLayer;
	GameMapLayer* gameMapLayer;
	TowerInfoLayer* towerInfoLayer;
	GameMapInfoLayer* gameMapInfoLayer;
};
