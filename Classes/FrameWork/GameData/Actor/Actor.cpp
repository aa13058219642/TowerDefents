#include "Actor.h"
#include "AnimateManager.h"
#include "ActorManager.h"

Actor::Actor()
{
	ID = -1;
	m_pos = Point::ZERO;
	m_defaultAnimate = "error";
	m_face = FACE_TO_RIGHT;

	m_parent = nullptr;
	m_sprite = nullptr;
	m_hpBar = nullptr;
	m_unitPos = nullptr;
	m_layer = nullptr;
}

Actor::Actor(int id, ActorData data, Layer* parent)
{
	ID = id;
	m_pos = Point::ZERO;
	m_face = FACE_TO_RIGHT;

	m_parent = parent;
	m_sprite = nullptr;
	m_hpBar = nullptr;
	m_unitPos = nullptr;

	m_defaultAnimate = data.defaultanimate;
	m_animateList = data.maps;

	this->bindSprite(m_parent);
}


Actor::~Actor()
{
	m_parent->removeChild(m_layer, true);
}

Actor* Actor::clone()
{
	Actor* actor = new Actor();
	actor->setDefaultAnimate( m_defaultAnimate);
	actor->setAnimateList(m_animateList);
	return actor;
}


void Actor::bindSprite(Layer* parent)
{
	m_parent = parent;

	m_layer = Layer::create();
	m_layer->setAnchorPoint(Point::ZERO);
	m_parent->addChild(m_layer,0);

	m_sprite = Sprite::create();
	m_sprite->setAnchorPoint(Vec2(0, 1));
	m_layer->addChild(m_sprite,1);
	this->playDefaultAnimate();
}


void Actor::setPos(Point pos)
{
	m_pos = pos;
	m_layer->setPosition(m_pos);
	m_layer->setLocalZOrder(Director::getInstance()->getVisibleSize().height - m_pos.y);
}

void Actor::setRotation(float rotation)
{
	m_sprite->setRotation(rotation);
}


void Actor::setDefaultAnimate(const Name& defaultAnimate)
{
	m_defaultAnimate = defaultAnimate;
}

void Actor::setAnimateList(map<Name, Name> animateList)
{
	this->m_animateList = animateList;
}


void Actor::changeFace(Face face)
{
	m_face = face;
	m_sprite->setFlippedX(m_face == FACE_TO_LEFT);
}




void Actor::playDefaultAnimate()
{
	m_sprite->stopAllActions();
	m_sprite->setColor(Color3B::WHITE);
	AnimateManager::getInstance()->playAnimate(m_defaultAnimate, m_sprite);
	Size size = m_sprite->getSpriteFrame()->getOriginalSize();
	m_sprite->setContentSize(size);
}


void Actor::playAction(const Name& actionName, float playtime, Color3B color)
{
	if (this->IsExistAnimate(actionName))
	{
		m_sprite->stopAllActions();
		m_sprite->setColor(color);
		//CallFunc* func = CallFunc::create(CC_CALLBACK_1(Sprite::runAction, m_sprite, AnimateManager::getInstance()->createAnimate(m_defaultAnimate)));
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(Actor::playDefaultAnimate, this));
		AnimateManager::getInstance()->playAnimate(m_animateList[actionName], m_sprite, playtime, func);
	}
	else
	{
		playDefaultAnimate();
	}

}

void Actor::playEffect(const Name& animateName, float playtime, Color3B color, Point offset, int localZOrder)
{
	Sprite* sprite = Sprite::create();
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, sprite));
	sprite->setLocalZOrder(localZOrder);
	sprite->setAnchorPoint(Vec2(0, 1));
	sprite->setPosition(offset );
	sprite->setColor(color);
	m_layer->addChild(sprite);
	AnimateManager::getInstance()->playAnimate(animateName, sprite, playtime, func);
}


void Actor::remove()
{
	//播放死亡动画，没有死亡动画的直接销毁
	if (this->IsExistAnimate("death"))
	{
		if (m_hpBar != nullptr)setShowHpBar(false);

		CallFunc* func = CallFunc::create([&](){
			ActorManager::getInstance()->destoryActor(ID); 
		});
		m_sprite->stopAllActions();
		AnimateManager::getInstance()->playAnimate(m_animateList["death"], m_sprite, 0, func);
	}
	else
	{
		ActorManager::getInstance()->destoryActor(ID);
	}
}



bool Actor::IsExistAnimate(const Name& animateName)
{
	return m_animateList.find(animateName) != m_animateList.end();
}


void Actor::setShowHpBar(bool isShow)
{
	if (m_hpBar == nullptr)
	{
		m_hpBar = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("hpBar.png");
		CCASSERT(m_hpBar != nullptr, "Actor::setShowHpBar(): hpBar.png NOT found");

		//Size size = m_sprite->getSpriteFrame()->getOriginalSize();
		//m_hpBar->setPosition(size.width / 2, size.height);
		m_hpBar->setPosition(-32, 100);
		m_hpBar->setContentSize(Size(64, 6));
		m_hpBar->setAnchorPoint(Point(0, 0.5));
		m_layer->addChild(m_hpBar,2);
	}
	m_hpBar->setVisible(isShow);
}

void Actor::setHpBarProgress(float progress)
{
	m_hpBar->setContentSize(Size(64 * progress, 6));
	//Size size = m_sprite->getSpriteFrame()->getOriginalSize();
	//m_hpBar->setPosition(-32, size.height);
}

void Actor::setShowUnitPos(bool isShow)
{
	if (m_unitPos == nullptr)
	{
		m_unitPos = Sprite::createWithSpriteFrameName("GridPos.png");
		CCASSERT(m_unitPos != nullptr, "Actor::setShowUnitPos(): GridPos.png NOT found");

		//m_unitPos->setContentSize(Size(64, 64));
		//m_unitPos->setAnchorPoint(Point::ZERO);
		//m_unitPos->setPosition(Point(-8,-8));
		m_unitPos->setLocalZOrder(0);
		//m_unitPos->setScale(Director::getInstance()->getContentScaleFactor());
		//Size size = m_sprite->getSpriteFrame()->getOriginalSize();
		//m_unitPos->setPosition(-32, 100);
		m_layer->addChild(m_unitPos);
	}
	m_unitPos->setVisible(isShow);
}














