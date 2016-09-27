#include "BattleScene.h"
#include "DebugDraw.h"

#include "GameMap.h"
#include "UnitManager.h"
#include "ActorManager.h"



BattleScene::BattleScene(){}

BattleScene::~BattleScene()
{

}


Scene* BattleScene::createScene(int level){
 	auto scene = Scene::create();
	Layer* layer;

	layer = BattleScene::create(level);
	scene->addChild(layer, 0);
	return scene;
}

BattleScene* BattleScene::create(int level)
{
	BattleScene* battleScene = new BattleScene();
	if (battleScene && battleScene->init(level))
	{
		battleScene->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(battleScene);
	}
	return battleScene;
}

bool BattleScene::init(int level)
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setContentSize(visibleSize);
	this->setScale(Director::getInstance()->getContentScaleFactor());
	this->setAnchorPoint(Point::ZERO);



	unitLayer = UnitLayer::create();
	this->addChild(unitLayer, 1);
	ActorManager::getInstance()->init(unitLayer);

	//init Map and Layer
	GameMap::getInstance()->init(level);

	towerSelectLayer = TowerSelectLayer::create();
	this->addChild(towerSelectLayer, 2);

	gameMapLayer = GameMapLayer::create();
	this->addChild(gameMapLayer, 0);

	towerInfoLayer = TowerInfoLayer::create();
	this->addChild(towerInfoLayer, 6000);

	if (DebugDraw::isDebug)
	{
		Node* layer;
		layer = DebugDraw::getInstance();
		this->addChild(layer, 9999);
	}

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt)
{
	GameMap::getInstance()->update(dt);

	towerInfoLayer->update(dt);
}

