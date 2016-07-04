#include "BattleScene.h"
#include "GameMap.h"
#include "GameObjectLayer.h"
#include "GameObjectTouchLayer.h"

BattleScene::BattleScene(){}

BattleScene::~BattleScene(){}


Scene* BattleScene::createScene(int level, bool isDebug){
 	auto scene = Scene::create();

	auto layer0 = BattleScene::create(isDebug);
	layer0->setDebug(isDebug);
	scene->addChild(layer0, 0);

	GameMap::getInstance()->LoadMap(level);

	auto layer = GameObjectLayer::create(isDebug);
	scene->addChild(layer, 1);

	auto layer2 = GameObjectTouchLayer::create(layer);
	scene->addChild(layer2, 2);

	return scene;
}

BattleScene* BattleScene::create(bool isDebug)
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
	if (!Layer::init())
	{
		return false;
	}


	if (m_isDebug){
		drawNode = DrawNode::create();
		this->addChild(drawNode);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("bg/bg_1.png");
	sprite->setScale(visibleSize.width / sprite->getContentSize().width);
	sprite->setAnchorPoint(Point(0, 0));
	////sprite->runAction(ActionManager::)
	this->addChild(sprite, 0);

	this->scheduleUpdate();

	return true;
}

void BattleScene::setDebug(bool isDebug){
	m_isDebug = isDebug;
}

void BattleScene::update(float dt)
{

}

