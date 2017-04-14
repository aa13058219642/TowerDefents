#include "BattleScene.h"
#include "DebugDraw.h"

#include "GameMap.h"
#include "UnitManager.h"
#include "ActorManager.h"
#include "BulletManager.h"
#include "MonsterManager.h"

BattleScene::BattleScene(){}

BattleScene::~BattleScene()
{

}

BattleScene* BattleScene::create()
{
	BattleScene* battleScene = new BattleScene();
	if (battleScene && battleScene->init())
	{
		battleScene->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(battleScene);
	}
	return battleScene;
}

bool BattleScene::init()
{
	if (!Scene::init())
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

	towerSelectLayer = TowerSelectLayer::create();
	this->addChild(towerSelectLayer, 2);

	gameMapLayer = GameMapLayer::create();
	this->addChild(gameMapLayer, 0);

	towerInfoLayer = TowerInfoLayer::create();
	this->addChild(towerInfoLayer, 6000);

	gameInfoLayer = GameInfoLayer::create();
	this->addChild(gameInfoLayer, 5999);

	LevelFinishLayer = LevelFinishLayer::create();
	LevelFinishLayer->setVisible(false);
	this->addChild(LevelFinishLayer, 6000);


	if (DebugDraw::isDebug)
	{
		Node* layer;
		layer = DebugDraw::getInstance();
		this->addChild(layer, 999999);
	}

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt)
{
	GameMap::getInstance()->update(dt);
}

void BattleScene::onExit()
{
	UnitManager::getInstance()->removeAllUnit();
	ActorManager::getInstance()->destoryAllActor();

	BehaviorManager::getInstance()->FreeAllResource();
	EffectManager::getInstance()->FreeAllResource();
	TextureManager::getInstance()->FreeAllResource();
	AnimateManager::getInstance()->FreeAllResource();
	ActorManager::getInstance()->FreeAllResource();
	SkillManager::getInstance()->FreeAllResource();
	BehaviorManager::getInstance()->FreeAllResource();
	WeaponManager::getInstance()->FreeAllResource();
	EffectManager::getInstance()->FreeAllResource();
	BulletManager::getInstance()->FreeAllResource();
	MonsterManager::getInstance()->FreeAllResource();
	GameMap::getInstance()->clear();

	Scene::onExit();
}
