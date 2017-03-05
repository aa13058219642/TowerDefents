#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "GridItem.h"

NS_CC_BEGIN
namespace ui {
	class Padding
	{
	public:
		Padding();
		Padding(float top, float left);
		Padding(float top, float left, float right, float bottom);
		~Padding();

		float top, left, right, bottom;
		static const Padding ZERO;
	};



	class GridView
	{
	public:
		GridView();
		~GridView();

		enum class Direction
		{
			VERTICAL,
			HORIZONTAL,
		};


		/*增加一个item*/
		virtual void addItem(GridItem* item) = 0;

		/*插入Item*/
		virtual void insertItem(int index, GridItem* item) = 0;

		/*取item*/
		virtual GridItem* getItem(int index) = 0;

		/*设置每个item的大小*/
		virtual void setItemSize(const Size& itemsize) = 0;

		/*设置内边距*/
		virtual void setPadding(const Padding& padding) = 0;

		/*设置滚动方向*/
		virtual void setDirection(GridView::Direction direction) = 0;

		/*行列之间的间距*/
		virtual void setSpacing(float horizontalSpacing, float verticalSpacing) = 0;

	protected:
		virtual void onSizeChanged() = 0;
		virtual void setItemPosition(int index, GridItem* item) = 0;

		virtual bool onTouchBegan(Touch* touch, Event* event) = 0;
		virtual void onTouchMoved(Touch* touch, Event* event) = 0;
		virtual void onTouchEnded(Touch* touch, Event* event) = 0;
		virtual void onTouchCancelled(Touch* touch, Event* event) = 0;


	};
}
NS_CC_END