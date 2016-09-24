#include "TowerInfoLayer.h"
#include "TowerDefentShare.h"
#include "UnitManager.h"


enum ETowerInfo :int{
	ETowerAttack, ETowerAP, ETowerMP, ETowerCD, ETowerRange, ETowerCri, ETowerSkill
};


TowerInfoLayer::TowerInfoLayer()
{ 
	m_parent = nullptr; 
	m_card = nullptr; 
}

TowerInfoLayer::~TowerInfoLayer(){}

TowerInfoLayer* TowerInfoLayer::create()
{
	TowerInfoLayer* layer = new TowerInfoLayer();
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

bool TowerInfoLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float scale = 1 / Director::getInstance()->getContentScaleFactor();
	centerPos = Point(visibleSize.width*scale / 2, visibleSize.height*scale / 2);

	this->setVisible(false);
	this->setPosition(centerPos);
	this->setAnchorPoint(Point::ZERO);

	//初始化layer
	m_bg = Sprite::createWithSpriteFrameName("TowerInfo_BG.png");
	this->addChild(m_bg);
	this->setContentSize(m_bg->getContentSize());

	//switchButton
	m_switchButton = Sprite::createWithSpriteFrameName("TowerInfo_switch.png");
	m_switchButton->setPosition(Point(337 * scale, 108.5 * scale) - centerPos);
	this->addChild(m_switchButton);

	//closeButton
	closeButton = Rect(Point(1152, 704), Size(96, 96));


	//label
	for (int i = 0; i < 8; i++)
	{
		m_label[i] = Label::createWithCharMap("fonts/TowerInfo_Number.png",24,42,' ');
		m_label[i]->setPosition(Point(900, 608 - i * 55)* scale - centerPos);
		//m_label[i]->setMaxLineWidth(360);
		m_label[i]->setWidth(320);
		m_label[i]->setHorizontalAlignment(TextHAlignment::RIGHT);
		//m_label[i]->setVisible(false);
		m_label[i]->setGlobalZOrder(6001);
		this->addChild(m_label[i]);
	}





	//设置Layer监听
	auto listener = EventListenerTouchOneByOne::create();

	//触摸按下
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};

	//触摸放开
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		if (this->isVisible())
		{
			Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());

			if (this->closeButton.containsPoint(pos))
			{
				this->close();
			}

			event->stopPropagation();
		}
	};
	//listener->setSwallowTouches(true);//截断触摸事件
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TowerInfoLayer::receiveMsg), Message_TowerInfoLayer, NULL);


	return true;
}

void TowerInfoLayer::receiveMsg(Ref* pData)
{
	CCASSERT(pData != NULL, "Notification Message Data == NULL");

	NotificationMsg msg = *(NotificationMsg*)pData;

	int id = msg.at("TowerID").asInt();
	m_parent = static_cast<Tower*>( UnitManager::getInstance()->getUnit(id));
	CCASSERT(m_parent != NULL, "TowerInfoLayer::receiveMsg  Tower == NULL");

	CWeapon * weapon = m_parent->getWeapon();
	float scale = 1 / Director::getInstance()->getContentScaleFactor();

	if (m_card != nullptr)
		m_card->removeFromParentAndCleanup(true);
	string str = StringUtils::format("card/card_%03d.png", (int)rand() % 8);
	Sprite* m_card = Sprite::create(str);
	m_card->setPosition(Point(336 * scale, 447.5 * scale) - centerPos);
	m_card->setScale(0.8*scale);
	this->addChild(m_card);

	m_label[ETowerAttack]->setString(StringUtils::format("%.0f-%.0f", (float)weapon->Damage.Min, (float)weapon->Damage.Max));
	m_label[ETowerAP]->setString(StringUtils::format("%.0f/%.0f", (float)m_parent->AP, (float)m_parent->AP.Max));
	m_label[ETowerMP]->setString(StringUtils::format("%.0f/%.0f", (float)m_parent->MP, (float)m_parent->MP.Max));
	m_label[ETowerCD]->setString(StringUtils::format("%.3fs", (float)weapon->ColdDown));
	m_label[ETowerRange]->setString(StringUtils::format("%.0f/%.0f", (float)weapon->Range / scale, (float)weapon->BoomRange / scale));
	m_label[ETowerCri]->setString(StringUtils::format("%.0f%%/%.0f%%", (float)weapon->criticalChance*100, (float)weapon->criticalMultiplier*100));


	this->show();
}


void TowerInfoLayer::update(float dt){

}


void TowerInfoLayer::show()
{

	this->stopAllActions();
	this->setVisible(true);
	this->setPosition(m_parent->getPos());
	this->setScale(0);
	this->runAction(Spawn::createWithTwoActions(ScaleTo::create(0.2f, 1), MoveTo::create(0.2f, centerPos)));
}

void TowerInfoLayer::close()
{
	CallFunc* func = CallFunc::create([&](){
		m_parent = nullptr;
		this->setVisible(false);
	});
	this->runAction(Spawn::createWithTwoActions(Sequence::createWithTwoActions(ScaleTo::create(0.1f, 0), func), MoveTo::create(0.1f, m_parent->getPos())));

}





