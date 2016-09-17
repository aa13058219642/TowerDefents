#include "BattleScene.h"
#include "DebugDraw.h"

#include "GameMap.h"
#include "UnitManager.h"
#include "ActorManager.h"

#include "UnitLayer.h"
#include "TowerSelectLayer.h"
#include "GameMapLayer.h"

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

	Node* layer;
	layer = UnitLayer::create();
	this->addChild(layer, 1);
	ActorManager::getInstance()->init(static_cast<Layer*>(layer));

	//init Map and Layer
	GameMap::getInstance()->init(level);
	
	if (DebugDraw::isDebug)
	{
		layer = DebugDraw::getInstance();
		this->addChild(layer, 9999);
	}


	layer = lay = TowerSelectLayer::create();
	this->addChild(layer, 2);

	layer = GameMapLayer::create();
	this->addChild(layer, 0);

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt)
{
	GameMap::getInstance()->update(dt);

}

