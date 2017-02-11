#include "GameMapLayer.h"
#include "GameMap\GameMap.h"

GameMapLayer::GameMapLayer(){}

GameMapLayer::~GameMapLayer(){}

GameMapLayer* GameMapLayer::create()
{
	GameMapLayer* layer = new GameMapLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(layer);
	}
	return layer;
}

bool GameMapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setAnchorPoint(Point::ZERO);
	this->addChild(GameMap::getInstance()->getMapLayer());


	//ÉèÖÃ¼àÌý
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		pos = pos / Director::getInstance()->getContentScaleFactor();
		//log("TouchPos:(%f,%f)", pos.x, pos.y);
		if (GameMap::getInstance()->onClick(pos))
		{
			event->stopPropagation();
		}
	};
	//listener->setSwallowTouches(true);//½Ø¶Ï´¥ÃþÊÂ¼þ
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
}

void GameMapLayer::update(float dt){

}








