#include "GridScrollView.h"

USING_NS_CC;
using namespace cocos2d::ui;


GridScrollView::GridScrollView()
{

}

GridScrollView::~GridScrollView()
{

}

GridScrollView* GridScrollView::create(const cocos2d::Size& viewsize, const Size& itemsize, GridView::Direction direction)
{
	GridScrollView* layer = new GridScrollView();
	if (layer && layer->init(viewsize, itemsize, direction))
	{
		layer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(layer);
	}
	return layer;
}

bool GridScrollView::init(const cocos2d::Size& viewsize, const Size& itemsize, GridView::Direction direction)
{
	if (!ui::ScrollView::init())
	{
		return false;
	}

	//Layer ³õÊ¼»¯
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	isMoved = false;
	horizontalSpacing = verticalSpacing = 0;
	m_padding = Padding::ZERO;


	this->setDirection(direction);
	this->setContentSize(viewsize);
	this->setItemSize(itemsize);
	this->setAnchorPoint(Point(0.5f, 0.5f));

	this->setScrollBarWidth(4);
	this->setScrollBarPositionFromCorner(Vec2(2, 2));
	this->setScrollBarColor(Color3B::WHITE);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GridScrollView::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GridScrollView::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GridScrollView::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GridScrollView::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GridScrollView::addItem(GridItem* item)
{
	int id = m_Items.size();
	item->id = id;
	m_Items.pushBack(item);
	this->addChild(item);

	//resetInnerSize();
	setItemPosition(id, item);
}

void  GridScrollView::insertItem(int index, GridItem* item)
{
	item->id = index;
	m_Items.insert(index, item);
	this->addChild(item);

	//resetInnerSize();
	setItemPosition(index, item);
}

GridItem*  GridScrollView::getItem(int index)
{
	for (auto& item : m_Items)
	{
		if (item->id == index)
			return item;
	}
	return nullptr;
}

void GridScrollView::setItemSize(const Size& itemsize)
{
	this->m_itemSize = itemsize;

	//this->resetInnerSize();
}

void  GridScrollView::setPadding(const Padding& padding)
{
	m_padding = padding;
}

void  GridScrollView::setDirection(GridView::Direction direction)
{
	switch (direction)
	{
	case cocos2d::ui::GridView::Direction::VERTICAL:
		ScrollView::setDirection(ScrollView::Direction::VERTICAL);
		break;
	case cocos2d::ui::GridView::Direction::HORIZONTAL:
		ScrollView::setDirection(ScrollView::Direction::HORIZONTAL);
		break;
	default:
		break;
	}
	//resetInnerSize();
}

void  GridScrollView::setSpacing(float horizontalSpacing, float verticalSpacing)
{
	this->horizontalSpacing = horizontalSpacing;
	this->verticalSpacing = verticalSpacing;
	//resetInnerSize();
}

void GridScrollView::resetInnerSize()
{
	Size layersize = this->getContentSize();
	Size innersize;

	switch (getDirection())
	{
	case cocos2d::ui::ScrollView::Direction::VERTICAL:
		if (layersize.width < m_itemSize.width)
		{
			this->m_numColumns = 0;
			this->removeAllChildren();
			return;
		}
		else
		{
			this->m_numColumns = 1 + (layersize.width - m_itemSize.width) / (m_itemSize.width + horizontalSpacing);
			innersize.width = m_numColumns*(m_itemSize.width + horizontalSpacing) - horizontalSpacing;

			this->m_numRows = (m_Items.size() % m_numColumns == 0 ? 0 : 1) + m_Items.size() / m_numColumns;
			innersize.height = m_numRows*(m_itemSize.height + verticalSpacing) - verticalSpacing;
		}
		break;
	case cocos2d::ui::ScrollView::Direction::HORIZONTAL:
		if (layersize.height < m_itemSize.height)
		{
			this->m_numRows = 0;
			this->removeAllChildren();
			return;
		}
		else
		{
			this->m_numRows = 1 + (layersize.height - m_itemSize.height) / (m_itemSize.height + verticalSpacing);
			innersize.height = m_numRows*(m_itemSize.height + verticalSpacing) - verticalSpacing;

			this->m_numColumns = (m_Items.size() % m_numRows == 0 ? 0 : 1) + m_Items.size() / m_numRows;
			innersize.width = m_numColumns*(m_itemSize.width + horizontalSpacing) - horizontalSpacing;
		}
		break;
	default:
		break;
	}
	this->setInnerContainerSize(innersize);

	if (m_numRows > 0 && m_numColumns > 0)
	{
		int s = m_Items.size();
		for (int i = 0; i < s; i++)
		{
			GridItem* item = m_Items.at(i);
			setItemPosition(i, item);
		}
	}
	else
	{
		this->removeAllChildren();
	}
}

void GridScrollView::onSizeChanged()
{
	ui::ScrollView::onSizeChanged();
}

void GridScrollView::setItemPosition(int index, GridItem* item)
{
	item->id = index;
	int px, py;
	Point pos;

	switch (getDirection())
	{
	case cocos2d::ui::ScrollView::Direction::VERTICAL:
		px = index % m_numColumns;
		py = index / m_numColumns;
		pos.x = px *(m_itemSize.width + horizontalSpacing);
		pos.y = this->getInnerContainerSize().height - (m_itemSize.height + py*(m_itemSize.height + verticalSpacing));
		break;		
	case cocos2d::ui::ScrollView::Direction::HORIZONTAL:
		px = index / m_numRows;
		py = index % m_numRows;
		pos.x = px*(m_itemSize.width + verticalSpacing);
		pos.y = this->getInnerContainerSize().height - py *(m_itemSize.width + horizontalSpacing) - m_itemSize.height;
		break;
	}



	item->setPosition(pos);
}

bool GridScrollView::onTouchBegan(Touch* touch, Event* event)
{
	ScrollView::onTouchBegan(touch, event);

	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	Rect rect = RectApplyAffineTransform(
		Rect(Point::ZERO, this->getContentSize()),
		this->getNodeToWorldAffineTransform());
	if (this->isVisible() && rect.containsPoint(pos))
	{

		int s = m_numColumns*m_numRows;
		for (int i = 0; i < s; i++)
		{
			if (i >= m_Items.size())
				break;

			auto item = m_Items.at(i);
			if (item->getBoundingBox().containsPoint(pos))
			{
				//log("onTouchBegan::tag=%d", item->getTag());
				item->onTouchBegan(touch, event);
			}
		}


		isMoved = false;
		return true;
	}
	else
	{
		return false;
	}
}

void GridScrollView::onTouchMoved(Touch* touch, Event* event)
{
	isMoved = true;
	ScrollView::onTouchMoved(touch, event);

	Point pos = convertTouchToNodeSpace(touch);
	int s = m_numColumns*m_numRows;
	for (int i = 0; i < s; i++)
	{
		if (i >= m_Items.size())
			break;

		auto item = m_Items.at(i);
		if (item->getBoundingBox().containsPoint(pos))
		{
			//log("onTouchBegan::tag=%d", item->getTag());
			item->onTouchMoved(touch, event);
		}
	}
}

void GridScrollView::onTouchEnded(Touch* touch, Event* event)
{
	ScrollView::onTouchEnded(touch, event);

	if (!isMoved)
	{
		Point pos = convertTouchToNodeSpace(touch);
		log("pos(%d,%d)", (int)pos.x, (int)pos.y);

		int s = m_numColumns*m_numRows;
		for (int i = 0; i < s; i++)
		{
			if (i >= m_Items.size())
				break;

			auto item = m_Items.at(i);
			if (item->getBoundingBox().containsPoint(pos))
			{
				//log("onTouchBegan::tag=%d", item->getTag());
				item->onTouchEnded(touch, event);
			}
		}
	}
	isMoved = false;

}

void GridScrollView::onTouchCancelled(Touch* touch, Event* event)
{
	ScrollView::onTouchCancelled(touch, event);

	Point pos = convertTouchToNodeSpace(touch);
	int s = m_numColumns*m_numRows;
	for (int i = 0; i < s; i++)
	{
		if (i >= m_Items.size())
			break;

		auto item = m_Items.at(i);
		if (item->getBoundingBox().containsPoint(pos))
		{
			//log("onTouchBegan::tag=%d", item->getTag());
			item->onTouchCancelled(touch, event);
		}
	}
}


