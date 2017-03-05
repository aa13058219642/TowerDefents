#pragma once
#include "cocos2d.h"
NS_CC_BEGIN
namespace ui {
	class GridItem :public cocos2d::Layer
	{
	public:
		int id;
		GridItem();
		~GridItem();
		virtual bool init();
		CREATE_FUNC(GridItem);

		virtual bool onTouchBegan(Touch* touch, Event* event);
		virtual void onTouchMoved(Touch* touch, Event* event);
		virtual void onTouchEnded(Touch* touch, Event* event);
		virtual void onTouchCancelled(Touch* touch, Event* event);
	};
}
NS_CC_END