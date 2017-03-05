#include "GridItem.h"
USING_NS_CC;
using namespace cocos2d::ui;

GridItem::GridItem(){};
GridItem::~GridItem(){};



bool GridItem::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}



bool GridItem::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void GridItem::onTouchMoved(Touch* touch, Event* event)
{

}

void GridItem::onTouchEnded(Touch* touch, Event* event)
{

}

void GridItem::onTouchCancelled(Touch* touch, Event* event)
{

}

