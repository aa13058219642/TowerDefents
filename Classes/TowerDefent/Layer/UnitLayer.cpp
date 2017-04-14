#include "UnitLayer.h"
#include "UnitManager.h"
#include "ActorManager.h"
#include "GameMap.h"

UnitLayer::UnitLayer()
{
}

UnitLayer::~UnitLayer()
{



}


UnitLayer* UnitLayer::create()
{
	UnitLayer* layer = new UnitLayer();
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

bool UnitLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bool flag = false;
	do{
		this->setAnchorPoint(Point::ZERO);

		//ÉèÖÃ¼àÌý
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [](Touch* touch, Event* event){
			return true;
		};

		listener->onTouchEnded = [&](Touch* touch, Event* event){
			Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
			pos = pos / Director::getInstance()->getContentScaleFactor();
			if (onClick(pos))
			{
				event->stopPropagation();

			}

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ActorManager::getInstance()->init(this);
		GameMap::getInstance()->bindActor();


		flag = true;
	} while (0);

	return flag;
}

void UnitLayer::update(float dt){

}

bool UnitLayer::onClick(Point pos)
{

	vector<CUnit*> vec = UnitManager::getInstance()->findUnit(EUnitType::Unit);
	for (auto obj : vec)
	{
		if (obj->isClickMe(pos))
		{
			obj->onClick();
			return true;

		}
	}
	return false;
}



