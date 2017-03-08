#include "GridPageView.h"

USING_NS_CC;
using namespace cocos2d::ui;

GridPageView::GridPageView()
{

}

GridPageView::~GridPageView()
{

}

GridPageView* GridPageView::create(const cocos2d::Size& viewsize, const Size& itemsize, GridView::Direction direction)
{
	GridPageView* layer = new GridPageView();
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

bool GridPageView::init(const cocos2d::Size& viewsize, const Size& itemsize, GridView::Direction direction)
{
	if (!ui::PageView::init())
	{
		return false;
	}

	//Layer ≥ı ºªØ
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	verticalSpacing = 0;
	horizontalSpacing = 0;
	isMoved = false;
	m_padding = Padding::ZERO;

	this->setContentSize(viewsize);
	this->setItemSize(itemsize);
	this->setDirection(direction);
	this->setAnchorPoint(Point(0.5f, 0.5f));

	Layout* layout = Layout::create();
	layout->setTag(0);
	layout->setTouchEnabled(false);
	m_pages.pushBack(layout);
	this->addPage(layout);



	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GridPageView::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GridPageView::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GridPageView::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GridPageView::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GridPageView::addItem(GridItem* item)
{
	int id = m_Items.size();
	item->id = id;
	m_Items.pushBack(item);

	setItemPosition(id, item);
}

void  GridPageView::insertItem(int index, GridItem* item)
{
	if (index > m_Items.size())
	{
		index = m_Items.size();
	}

	if (index == m_Items.size())
	{
		this->addItem(item);
	}
	else
	{
		item->id = index;
		m_Items.insert(index, item);
		setItemPosition(index, item);


		int s = m_Items.size();
		for (int i = 0; i < s; i++)
		{
			GridItem* item = m_Items.at(i);
			item->id = i;
			setItemPosition(i, item);
		}
	}
}

GridItem*  GridPageView::getItem(int index)
{
	for (auto& item : m_Items)
	{
		if (item->id == index)
			return item;
	}
	return nullptr;
}

void GridPageView::removeItem(int index)
{
	for (auto& item : m_Items)
	{
		if (item->id == index)
		{
			item->removeFromParent();
			m_Items.eraseObject(item);
			break;
		}
	}

	//÷ÿ≈≈item
	int s = m_Items.size();
	for (int i = 0; i < s; i++)
	{
		GridItem* item = m_Items.at(i);
		setItemPosition(i, item);
	}
}


void GridPageView::setItemSize(const Size& itemsize)
{
	this->m_itemSize = itemsize;
	this->onSizeChanged();
}

void  GridPageView::setPadding(const Padding& padding)
{
	m_padding = padding;
}

void  GridPageView::setDirection(GridView::Direction direction)
{
	switch (direction)
	{
	case cocos2d::ui::GridView::Direction::VERTICAL:
		PageView::setDirection(PageView::Direction::VERTICAL);
		break;
	case cocos2d::ui::GridView::Direction::HORIZONTAL:
		PageView::setDirection(PageView::Direction::HORIZONTAL);
		break;
	default:
		break;
	}

}

void  GridPageView::setSpacing(float horizontalSpacing, float verticalSpacing)
{
	this->horizontalSpacing = horizontalSpacing;
	this->verticalSpacing = verticalSpacing;
}


void GridPageView::doLayout()
{
	if (!_doLayoutDirty)
	{
		return;
	}

	this->updateAllPagesPosition();
	updateAllPagesSize();
	updateBoundaryPages();


	_doLayoutDirty = false;
}


void GridPageView::updateAllPagesPosition()
{
	ssize_t pageCount = this->getPageCount();

	if (pageCount <= 0)
	{
		_curPageIdx = -1;
		return;
	}

	if (_curPageIdx >= pageCount)
	{
		_curPageIdx = pageCount - 1;
	}
	// If the layout is dirty, don't trigger auto scroll
	_isAutoScrolling = false;

	for (int i = 0; i<pageCount; i++)
	{
		Layout* page = _pages.at(i);
		Vec2 newPosition;

		if (_direction == PageView::Direction::HORIZONTAL)
		{
			float pageWidth = getContentSize().width;
			newPosition = Vec2((i - _curPageIdx) * (pageWidth+horizontalSpacing) , 0);
		}
		else if (_direction == PageView::Direction::VERTICAL)
		{
			float pageHeight = getContentSize().height;
			newPosition = Vec2(0, (i - _curPageIdx) * (pageHeight + verticalSpacing) * -1);

		}
		page->setPosition(newPosition);
	}
}

void GridPageView::onSizeChanged()
{
	ui::PageView::onSizeChanged();

	Size size = this->getContentSize();

	if (size.width < m_itemSize.width)
		this->m_numColumns = 0;
	else
		this->m_numColumns = 1 + ((size.width - m_itemSize.width) / (m_itemSize.width + horizontalSpacing));

	if (size.height < m_itemSize.height)
		this->m_numRows = 0;
	else
		this->m_numRows = 1 + ((size.height - m_itemSize.height) / (m_itemSize.height + verticalSpacing));

	if (m_numRows > 0 && m_numColumns > 0)
	{
		m_pages.clear();
		this->removeAllPages();

		int s = m_Items.size();
		for (int i = 0; i < s;i++)
		{
			GridItem* item = m_Items.at(i);
			setItemPosition(i, item);
		}
	}
	else
	{
		m_pages.clear();
		this->removeAllPages();
	}
}

void GridPageView::setItemPosition(int index, GridItem* item)
{
	if (index >= m_numColumns*m_numRows*m_pages.size())
	{
		Layout* layout = Layout::create();
		layout->setTag(m_pages.size());
		m_pages.pushBack(layout);
		this->addPage(layout);
	}

	if (item->getParent() != nullptr)
	{
		item->removeFromParent();
	}
	int page_id = index / (m_numColumns*m_numRows);
	int pid = index % (m_numColumns*m_numRows);
	item->id = index;
	m_pages.at(page_id)->addChild(item);

	int px = pid % m_numColumns;
	int py = pid / m_numColumns;

	Point pos;
	pos.x =  px *(m_itemSize.width + horizontalSpacing);
	pos.y = this->getContentSize().height - (m_itemSize.height + py*(m_itemSize.height + verticalSpacing));

	item->setPosition(pos);
}

bool GridPageView::onTouchBegan(Touch* touch, Event* event)
{
	PageView::onTouchBegan(touch, event);

	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	Rect rect = RectApplyAffineTransform(
		Rect(Point::ZERO, this->getContentSize()),
		this->getNodeToWorldAffineTransform());
	if (this->isVisible() && rect.containsPoint(pos) && m_Items.size() > 0)
	{
		int s = m_numColumns*m_numRows;
		for (int i = 0; i < s; i++)
		{
			int click_index = this->getCurPageIndex()*s + i;
			if (click_index >= m_Items.size())
				break;

			auto item = m_Items.at(this->getCurPageIndex()*s + i);
			if (item->getBoundingBox().containsPoint(pos))
			{
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

void GridPageView::onTouchMoved(Touch* touch, Event* event)
{
	isMoved = true;
	PageView::onTouchMoved(touch, event);

	Point pos = convertTouchToNodeSpace(touch);
	int s = m_numColumns*m_numRows;
	for (int i = 0; i < s; i++)
	{
		int click_index = this->getCurPageIndex()*s + i;
		if (click_index >= m_Items.size())
			break;

		auto item = m_Items.at(this->getCurPageIndex()*s + i);
		if (item->getBoundingBox().containsPoint(pos))
		{
			item->onTouchMoved(touch, event);
		}
	}



}

void GridPageView::onTouchEnded(Touch* touch, Event* event)
{
	PageView::onTouchEnded(touch, event);

	if (!isMoved)
	{
		Point pos = convertTouchToNodeSpace(touch);
		log("pos(%d,%d)", (int)pos.x, (int)pos.y);

		int s = m_numColumns*m_numRows;
		for (int i = 0; i < s; i++)
		{
			int click_index = this->getCurPageIndex()*s + i;
			if (click_index >= m_Items.size())
				break;

			auto item = m_Items.at(this->getCurPageIndex()*s + i);
			if (item->getBoundingBox().containsPoint(pos))
			{
				log("index=%d", item->id);
				item->onTouchEnded(touch, event);
			}
		}
	}
	isMoved = false;

}

void GridPageView::onTouchCancelled(Touch* touch, Event* event)
{
	PageView::onTouchCancelled(touch, event);

	Point pos = convertTouchToNodeSpace(touch);
	int s = m_numColumns*m_numRows;
	for (int i = 0; i < s; i++)
	{
		int click_index = this->getCurPageIndex()*s + i;
		if (click_index >= m_Items.size())
			break;

		auto item = m_Items.at(this->getCurPageIndex()*s + i);
		if (item->getBoundingBox().containsPoint(pos))
		{
			item->onTouchCancelled(touch, event);
		}
	}
}




