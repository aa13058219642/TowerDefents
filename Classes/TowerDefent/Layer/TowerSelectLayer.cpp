#include "TowerSelectLayer.h"
#include "TowerDefentShare.h"
#include "GameMap.h"
#include "Tower.h"
#include "SpellCardManager.h"
#include "TowerCardManager.h"
#include "Player.h"
#include "GameConfig.h"
//using namespace cocos2d::ui;

TowerSelectLayer::TowerSelectLayer(){
	m_gridPos = nullptr;
	m_state = ETowerSelectLayerState::UnShow;
}

TowerSelectLayer::~TowerSelectLayer()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

TowerSelectLayer* TowerSelectLayer::create()
{
	TowerSelectLayer* layer = new TowerSelectLayer();
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

bool TowerSelectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Layer 初始化
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setContentSize(visibleSize);
	this->setPosition(Point::ZERO);
	this->setAnchorPoint(Point::ZERO);
	this->setVisible(false);

	selectLayer = Layer::create();
	selectLayer->setContentSize(Size(256,256));
	selectLayer->setAnchorPoint(Point::ZERO);
	this->addChild(selectLayer);

	//其他
	this->initSprite();
	this->initListener();


	return true;
}

void TowerSelectLayer::initSprite()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	//背景圈
	bg_circle = Sprite::createWithSpriteFrameName("TowerSelect_BGCircle.png");
	bg_circle->runAction(RepeatForever::create(RotateBy::create(60, 360)));
	selectLayer->addChild(bg_circle);

	//建塔按钮
	bt_center = Sprite::createWithSpriteFrameName("TowerSelect_BuildTower.png");
	bt_center->setVisible(false);
	selectLayer->addChild(bt_center);

	//升级按钮
	float dis = 1.414213f * 82 / Director::getInstance()->getContentScaleFactor();

	for (int i = 0; i < 8; i++)
	{
		a_layer[i] = Layer::create();
		Point pos(dis, 0);
		switch (i)
		{
		case North:		pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS( 90)); break;
		case NorthWest:	pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(135)); break;
		case West:		pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(180)); break;
		case SouthWest:	pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(225)); break;
		case South:		pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(270)); break;
		case SouthEast:	pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(315)); break;
		case East:		pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS(  0)); break;
		case NorthEast:	pos.rotate(Point::ZERO, CC_DEGREES_TO_RADIANS( 45)); break;
		default:CCASSERT(false, "Unknow Direction"); break;
		}
		a_layer[i]->setPosition(pos);
		a_layer[i]->setVisible(false);


		a_bt[i] = Sprite::create();
		a_bt[i]->setGlobalZOrder(5000);
		a_layer[i]->addChild(a_bt[i]);

		a_bg[i] = Sprite::createWithSpriteFrameName("TowerSelect_CostBox.png");
		a_bg[i]->setPosition(Point(0,-40));
		a_bg[i]->setVisible(false);
		a_layer[i]->addChild(a_bg[i]);

		a_number[i] = Label::createWithCharMap("fonts/TowerSelect_CostNumber.png", 8, 16, '0');
		a_number[i]->setPosition(Point(0, -39));
		a_number[i]->setHorizontalAlignment(TextHAlignment::CENTER);
		a_number[i]->setVisible(false);
		a_number[i]->setGlobalZOrder(5001);
		a_layer[i]->addChild(a_number[i],5001);

		selectLayer->addChild(a_layer[i]);
	}

	//cocos2d::ui::Button* bt = cocos2d::ui::Button::create("", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
}

void TowerSelectLayer::initListener()
{
	//设置Layer监听
	auto listener = EventListenerTouchOneByOne::create();

	//触摸按下
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};

	//触摸放开
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		if (this->isVisible() && m_gridPos != nullptr)
		{
			Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
			if (this->onClick(pos))
			{
				event->stopPropagation();
			}
			else
			{
				this->cancel();
			}
		}
	};
	//listener->setSwallowTouches(true);//截断触摸事件
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->msgSubscribe(Message_Global);

	//订阅消息
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TowerSelectLayer::receiveMsg), Message_TowerSelectLayer, NULL);
}

void TowerSelectLayer::receiveMsg(Ref* pData)
{
	CCASSERT(pData != NULL, "Notification Message Data == NULL");

	NotificationMsg msg = *(NotificationMsg*)pData;
	int cmd = msg.at("cmd").asInt();
	switch (cmd)
	{
	case MsgCMD::TowerSelectLayer_ClickEmptyGridPos:
		showFor_EmptyPos(msg);
		break;
	case MsgCMD::TowerSelectLayer_ClickTowerGridPos:
		showFor_TowerPos(msg);
		break;
	case MsgCMD::TowerSelectLayer_ClickSpellEmptyGridPos:
		showFor_BuildSpellTower(msg);
		break;
	case MsgCMD::TowerSelectLayer_ClickSpellTowerGridPos:
		showFor_SpellPos(msg);
		break;
	default:
		CCASSERT(false, "Unkow notification message command");
		break;
	
	}
}


void TowerSelectLayer::receive(const Message* message)
{
	if (message->keyword == "updateMoney")
	{
		updateMoney();
	}
}





void TowerSelectLayer::update(float dt){

}


void TowerSelectLayer::show()
{
	selectLayer->stopAllActions();
	this->setVisible(true);
	selectLayer->setScale(0);
	selectLayer->runAction(ScaleTo::create(0.2f, 1));
}

void TowerSelectLayer::cancel()
{
	m_gridPos = nullptr;
	m_state = ETowerSelectLayerState::UnShow;

	CallFunc* func = CallFunc::create([&](){
		this->setVisible(false); 
		selectLayer->setPosition(Point::ZERO);
	});
	selectLayer->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.1f, 0), func));
}

void TowerSelectLayer::hideAllButton()
{
	bt_center->setVisible(false);
	for (int i = 0; i < 8; i++)
	{
		a_layer[i]->setVisible(false);
		a_bg[i]->setVisible(false);
		a_number[i]->setVisible(false);
	}
}

void TowerSelectLayer::showFor_EmptyPos(const NotificationMsg& msg)
{
	Point pos = Point(msg.at("x").asFloat(), msg.at("y").asFloat());
	if (selectLayer->getPosition() != pos)//若是layer已经在pos处了，不进行操作
	{
		m_state = ETowerSelectLayerState::ShowFor_EmptyPos;
		m_gridPos = (GridPos*)msg.at("GridPos").asInt();
		selectLayer->setPosition(pos);
		this->hideAllButton();

		bt_center->setSpriteFrame("TowerSelect_BuildTower.png");
		bg_circle->setColor(Color3B::WHITE);
		bt_center->setVisible(true);

		this->show();
	}
}

void TowerSelectLayer::showFor_TowerPos(const NotificationMsg& msg)
{
	Point pos = Point(msg.at("x").asFloat(), msg.at("y").asFloat());
	if (m_state != ETowerSelectLayerState::ShowFor_TowerPos &&
		selectLayer->getPosition() != pos)//若是layer已经在pos处了，不进行操作
	{
		m_state = ETowerSelectLayerState::ShowFor_TowerPos;
		m_gridPos = (GridPos*)msg.at("GridPos").asInt();
		selectLayer->setPosition(pos);
		this->hideAllButton();

		//升级位按钮
		a_bt[Direction::NorthWest]->setSpriteFrame("TowerSelect_SpellPos.png");
		a_layer[Direction::NorthWest]->setVisible(true);

		//塔信息按钮
		a_bt[Direction::NorthEast]->setSpriteFrame("TowerSelect_TowerInfo.png");
		a_layer[Direction::NorthEast]->setVisible(true);

		//变卖按钮
		a_bt[Direction::South]->setSpriteFrame("TowerSelect_Sell.png");
		a_number[Direction::South]->setString("6666");
		a_number[Direction::South]->setVisible(true);
		a_bg[Direction::South]->setVisible(true);
		a_layer[Direction::South]->setVisible(true);

		//改变背景圈颜色
		Color3B color = Color3B(msg.at("color_r").asInt(), msg.at("color_g").asInt(), msg.at("color_b").asInt());
		bg_circle->setColor(color);
		
		this->show();
	}
}

void TowerSelectLayer::showFor_SpellPos(const NotificationMsg& msg)
{
	Point pos = Point(msg.at("x").asFloat(), msg.at("y").asFloat());
	if (m_state != ETowerSelectLayerState::ShowFor_SpellPos &&
		selectLayer->getPosition() != pos)//若是layer已经在pos处了，不进行操作
	{
		m_state = ETowerSelectLayerState::ShowFor_SpellPos;
		m_gridPos = (GridPos*)msg.at("GridPos").asInt();
		selectLayer->setPosition(pos);
		this->hideAllButton();

		//变卖按钮
		a_bt[Direction::South]->setSpriteFrame("TowerSelect_Sell.png");
		a_number[Direction::South]->setString("333");
		a_number[Direction::South]->setVisible(true);
		a_bg[Direction::South]->setVisible(true);
		a_layer[Direction::South]->setVisible(true);

		//改变背景圈颜色
		Color3B color = Color3B(msg.at("color_r").asInt(), msg.at("color_g").asInt(), msg.at("color_b").asInt());
		bg_circle->setColor(color);

		this->show();
	}
}

void TowerSelectLayer::showFor_BuildTower()
{
	if (m_state != ETowerSelectLayerState::ShowFor_BuildTower)
	{
		m_state = ETowerSelectLayerState::ShowFor_BuildTower;

		this->hideAllButton();
		for (int i = 0; i < 8; i++)
		{
			a_bt[i]->setSpriteFrame(StringUtils::format("Tower_%03d.png", i));
			//a_bt[i]->setSpriteFrame("TowerSelect_BuildTower.png");
			a_number[i]->setVisible(true);
			a_bg[i]->setVisible(true);
			a_layer[i]->setVisible(true);
		}
		this->updateMoney();
		this->show();
	}
}

void TowerSelectLayer::showFor_BuildSpellPos()
{
	if (m_state != ETowerSelectLayerState::ShowFor_BuildSpellPos)
	{
		m_state = ETowerSelectLayerState::ShowFor_BuildSpellPos;
		this->hideAllButton();

		const int* around = m_gridPos->getAroundGridPosID();
		auto gamemap = GameMap::getInstance();
		for (int i = 0; i < 8; i++)
		{
			if (around[i] != -1 && gamemap->getGridPos(around[i])->getType() == EGridPosType::GridPosType_Empty)
			{
				a_bt[i]->setSpriteFrame(StringUtils::format("TowerSelect_SpellPos_%03d.png", i));
				a_number[i]->setVisible(true);
				a_bg[i]->setVisible(true);
				a_layer[i]->setVisible(true);
			}
		}
		this->updateMoney();
		this->show();
	}
}

void TowerSelectLayer::showFor_BuildSpellTower(const NotificationMsg& msg)
{
	Point pos = Point(msg.at("x").asFloat(), msg.at("y").asFloat());
	if (m_state != ETowerSelectLayerState::ShowFor_BuildSpellTower &&
		selectLayer->getPosition() != pos)//若是layer已经在pos处了，不进行操作
	{
		m_state = ETowerSelectLayerState::ShowFor_BuildSpellTower;
		m_gridPos = (GridPos*)msg.at("GridPos").asInt();
		selectLayer->setPosition(pos);
		this->hideAllButton();

		bt_center->setSpriteFrame("TowerSelect_Sell.png");
		bt_center->setVisible(true);

		const int* around = m_gridPos->getAroundGridPosID();
		auto gamemap = GameMap::getInstance();

		//const Name* spellcard = gamemap->getSpellCard();
		auto spellcard = Player::getInstance()->getSpellCard();
		int size = spellcard.size();
		for (int i = 0; i < size; i++)
		{
			if (!spellcard[i].name.empty())
			{
				a_bt[i]->setSpriteFrame(StringUtils::format("TowerSelect_SpellTower_%03d.png", spellcard[i].Icon));
				a_number[i]->setVisible(true);
				a_bg[i]->setVisible(true);
				a_layer[i]->setVisible(true);
			}
		}
		this->updateMoney();
		this->show();
	}
}



bool TowerSelectLayer::onClick(Point pos)
{
	

	//计算被点击的按钮( 0-7=a_bt, 8=bt_center, -1=无)
	int index = -1;
	do{
		if (bt_center->isVisible())
		{
			Rect rect = RectApplyAffineTransform(
				Rect(Point::ZERO, bt_center->getContentSize()), 
				bt_center->getNodeToWorldAffineTransform());
			if (bt_center->isVisible() && rect.containsPoint(pos))
			{
				index = Direction::Center;
				break;
			}
			//bt_buildTower->setSpriteFrame("bt_BuildTower_A.png");
		}

		for (int i = 0; i < 8; i++)
		{
			//bt_upgrade[i]->setSpriteFrame("bt_UpgradePos_A.png");
			if (a_layer[i]->isVisible())
			{
				Rect rect = RectApplyAffineTransform(
					Rect(Point::ZERO, a_bt[i]->getContentSize()), 
					a_bt[i]->getNodeToWorldAffineTransform());
				if (rect.containsPoint(pos))
				{
					index = i;
					break;
				}
			}
		}
	} while (0);
	

	switch (m_state)
	{
	case ETowerSelectLayerState::ShowFor_EmptyPos:
		if (index == Direction::Center)
			clickEvent_showLayerFor_BuildTower();
		break;
	case ETowerSelectLayerState::ShowFor_TowerPos:
		if (index == Direction::NorthWest)
			clickEvent_showLayerFor_BuildSpellPos();
		else if (index == Direction::NorthEast)
			clickEvent_showLayerFor_TowerInfo();
		else if (index == Direction::South)
			clickEvent_sellTower();
		break;
	case ETowerSelectLayerState::ShowFor_SpellPos:
		if (index == Direction::South)
			clickEvent_sellSpellTower();
		break;
	case ETowerSelectLayerState::ShowFor_BuildTower:
		if (index >= Direction::North && index <= Direction::NorthEast)
			clickEvent_buildTower((Direction)index);
		break;
	case ETowerSelectLayerState::ShowFor_BuildSpellPos:
		if (index >= Direction::North && index <= Direction::NorthEast)
			clickEvent_buildSpellPos((Direction)index);
		break;
	case ETowerSelectLayerState::ShowFor_BuildSpellTower:
		if (index >= Direction::North && index <= Direction::NorthEast)
			clickEvent_buildSpellTower((Direction)index);
		else if (index == Direction::Center)
			clickEvent_sellSpellPos();
		break;
	default:
		break;
	}
	
	return (index != -1) ? true : false;
}

void TowerSelectLayer::clickEvent_showLayerFor_TowerInfo()
{
	//log("clickEvent_showLayerFor_TowerInfo");

	NotificationMsg msg;
	msg["TowerID"] = m_gridPos->getTower()->ID;
	NotificationCenter::getInstance()->postNotification(Message_TowerInfoLayer, (Ref*)&msg);


	this->cancel();
}

void TowerSelectLayer::clickEvent_showLayerFor_BuildTower()
{
	//log("clickEvent_showLayerFor_BuildTower");
	this->showFor_BuildTower();
}

void TowerSelectLayer::clickEvent_showLayerFor_BuildSpellPos()
{
	//log("clickEvent_showLayerFor_BuildSpellPos");
	this->showFor_BuildSpellPos();
}

void TowerSelectLayer::clickEvent_buildTower(Direction dir)
{
	//log("clickEvent_buildTower");
	Player* player = Player::getInstance();
	TowerCard towercard = player->getTowerCard()[dir];
	if (towercard.price.isCanPay(player))
	{
		player->addTowerPrice(dir, TowerPriceAddition);
		towercard.price.payCost(player);
		m_gridPos->buildTower(towercard);
	}
	this->cancel();
}

void TowerSelectLayer::clickEvent_buildSpellPos(Direction dir)
{
	//log("clickEvent_buildSpellPos");
	Player* player = Player::getInstance();
	if (price[dir].isCanPay(player))
	{
		price[dir].payCost(player);
		m_gridPos->getTower()->buildSpellTowerPos(dir);
		GridPos* GridPos = GameMap::getInstance()->getGridPos(m_gridPos->getAroundGridPosID(dir));
		GridPos->buildSpellPos(m_gridPos->getTower(), dir);
	}
	this->cancel();
}

void TowerSelectLayer::clickEvent_buildSpellTower(Direction dir)
{
	//log("clickEvent_buildSpellTower");
	Player* player = Player::getInstance();
	SpellCard spellcard = player->getSpellCard()[dir];
	if (spellcard.price.isCanPay(player))
	{
		player->addSpellPrice(dir, SpellTowerPriceAddition);
		spellcard.price.payCost(player);
		m_gridPos->buildSpellTower(spellcard);
	}

	this->cancel();
}

void TowerSelectLayer::clickEvent_sellTower()
{
	//log("clickEvent_sellTower");
	this->cancel();
}

void TowerSelectLayer::clickEvent_sellSpellPos()
{
	//log("clickEvent_sellSpellPos");
	this->cancel();
}

void TowerSelectLayer::clickEvent_sellSpellTower()
{
	//log("clickEvent_sellSpellTower");
	this->cancel();
}







void TowerSelectLayer::updateMoney()
{
	float money = Player::getInstance()->getMoney();
	int size;
	if (m_state == ETowerSelectLayerState::ShowFor_BuildTower)
	{
		auto towercard = Player::getInstance()->getTowerCard();
		size = towercard.size();
		for (int i = 0; i < size; i++)
		{
			price[i].money = towercard[i].price.money;
		}

	}
	else if (m_state == ETowerSelectLayerState::ShowFor_BuildSpellPos)
	{
		const int* around = m_gridPos->getAroundGridPosID();
		
		size = 8;
		int SpellPosCount = m_gridPos->getTower()->getSpellPosCount();
		TowerCard towercard = m_gridPos->getTower()->getTowerCard();
		for (int i = 0; i < 8; i++)
		{
			price[i].money = towercard.spellPosPrice[i] + SpellPosCount * SpellPosPriceAddition;
		}
	}
	else if (m_state == ETowerSelectLayerState::ShowFor_BuildSpellTower)
	{
		auto spellcard = Player::getInstance()->getSpellCard();
		size = spellcard.size();
		for (int i = 0; i < size; i++)
		{
			price[i].money = spellcard[i].price.money;
		}
	}
	else
	{
		return;
	}

	for (int i = 0; i < size; i++)
	{
		a_number[i]->setString(StringUtils::format("%d", (int)price[i].money));
		if (money < price[i].money)
		{
			a_number[i]->setColor(Color3B::RED);
		}
		else
		{
			a_number[i]->setColor(Color3B::WHITE);
		}
	}
}
