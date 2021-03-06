#include "CActor.h"
#include "AnimateManager.h"
#include "ActorManager.h"

using namespace cocosgalaxy;

CActor::CActor()
{
	ID = -1;
	m_pos = Point::ZERO;
	m_defaultAnimate = "error";
	m_face = FACE_TO_RIGHT;
	LocalLevel = 0;

	m_parent = nullptr;
	m_sprite = nullptr;
	m_hpBar = nullptr;
	m_unitPos = nullptr;
	m_layer = nullptr;
	m_spriteLayer = nullptr;
}

CActor::CActor(int id, ActorData data, Layer* parent)
{
	ID = id;
	m_pos = Point::ZERO;
	m_face = FACE_TO_RIGHT;
	LocalLevel = 1;

	m_parent = parent;
	m_sprite = nullptr;
	m_hpBar = nullptr;
	m_unitPos = nullptr;

	m_defaultAnimate = data.defaultanimate;
	m_animateList = data.maps;


	this->bindSprite(m_parent);
}


CActor::~CActor()
{
	//m_parent->removeChild(m_layer, true);
	m_layer->removeFromParent();
}

CActor* CActor::clone()
{
	CActor* actor = new CActor();
	actor->setDefaultAnimate( m_defaultAnimate);
	actor->setAnimateList(m_animateList);
	return actor;
}


void CActor::bindSprite(Layer* parent)
{
	m_parent = parent;

	m_layer = Layer::create();
	m_layer->setAnchorPoint(Point::ZERO);
	m_parent->addChild(m_layer,0);

	m_spriteLayer = Layer::create();
	m_spriteLayer->setAnchorPoint(Point::ZERO);
	m_layer->addChild(m_spriteLayer);

	m_sprite = Sprite::create();
	m_sprite->setAnchorPoint(Vec2(0, 1));
	m_spriteLayer->addChild(m_sprite, 1);
	this->playDefaultAnimate();
}


void CActor::setPos(Point pos)
{
	m_pos = pos;
	m_layer->setPosition(m_pos);
	m_layer->setLocalZOrder(Director::getInstance()->getVisibleSize().height*(LocalLevel + 1) - m_pos.y);
}

void CActor::setRotation(float rotation)
{
	m_spriteLayer->setRotation(rotation);
}


void CActor::setDefaultAnimate(const Name& defaultAnimate)
{
	m_defaultAnimate = defaultAnimate;
}

void CActor::setAnimateList(map<Name, Name> animateList)
{
	this->m_animateList = animateList;
}

void CActor::setLocalLevel(int level)
{
	this->LocalLevel = level;
	m_layer->setLocalZOrder(Director::getInstance()->getVisibleSize().height*(LocalLevel + 1) - m_pos.y);
}


void CActor::changeFace(Face face)
{
	m_face = face;
	//m_sprite->setFlippedX(m_face == FACE_TO_LEFT);
	if (m_face == FACE_TO_LEFT)
	{
		m_spriteLayer->setRotationSkewY(0);
	}
	else
	{
		m_spriteLayer->setRotationSkewY(180);
	}
}




void CActor::playDefaultAnimate()
{
	m_sprite->stopAllActions();
	m_sprite->setColor(Color3B::WHITE);
	AnimateManager::getInstance()->playAnimate(m_defaultAnimate, m_sprite);
	Size size = m_sprite->getSpriteFrame()->getOriginalSize();
	m_sprite->setContentSize(size);
}


void CActor::playAction(const Name& actionName, float playtime, Color3B color)
{
	if (this->IsExistAnimate(actionName))
	{
		m_sprite->stopAllActions();
		m_sprite->setColor(color);
		//CallFunc* func = CallFunc::create(CC_CALLBACK_1(Sprite::runAction, m_sprite, AnimateManager::getInstance()->createAnimate(m_defaultAnimate)));
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(CActor::playDefaultAnimate, this));
		AnimateManager::getInstance()->playAnimate(m_animateList[actionName], m_sprite, playtime, func);
	}
	else
	{
		//CCASSERT(false, StringUtils::format("Action [%s] NOT found !", actionName).c_str());
		playDefaultAnimate();
	}

}

void CActor::playEffect(const Name& animateName, float playtime, Color3B color, Point offset, int localZOrder, int tag)
{
	Sprite* sprite = Sprite::create();
	sprite->setName(animateName);
	sprite->setTag(tag);
	sprite->setLocalZOrder(localZOrder);
	sprite->setAnchorPoint(Vec2(0, 1));
	sprite->setPosition(offset );
	sprite->setColor(color);
	m_spriteLayer->addChild(sprite);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, sprite));
	AnimateManager::getInstance()->playAnimate(animateName, sprite, playtime, func);
}


void CActor::remove()
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

void CActor::removeEffect(const Name& animateName, int tag)
{
	Vector<Node*> childs = m_layer->getChildren();

	for (Node* child : childs)
	{
		if (child->getTag() == tag && child->getName() == animateName)
		{
			child->removeFromParent();
			return;
		}
	}
}





bool CActor::IsExistAnimate(const Name& animateName)
{
	return m_animateList.find(animateName) != m_animateList.end();
}

void CActor::setShowHpBar(bool isShow, Rect rect)
{
	if (m_hpBar == nullptr)
	{
		m_hpBar = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("hpBar.png");
		CCASSERT(m_hpBar != nullptr, "CActor::setShowHpBar(): hpBar.png NOT found");

		//Size size = m_sprite->getSpriteFrame()->getOriginalSize();
		//m_hpBar->setPosition(size.width / 2, size.height);

		float f = Director::getInstance()->getContentScaleFactor();
		rect.size = rect.size*f;
		hpbarRect = rect;
		m_hpBar->setPosition(hpbarRect.origin);
		m_hpBar->setContentSize(hpbarRect.size);
		m_hpBar->setAnchorPoint(Point(0, 0.5));
		m_layer->addChild(m_hpBar, 9999);
	}
	m_hpBar->setVisible(isShow);
}



void CActor::setHpBarProgress(float progress)
{
	if (m_hpBar != nullptr)
	{
		clampf(progress, 0, 100);
		if (progress > 0)
		{
			m_hpBar->setVisible(true);
			m_hpBar->setContentSize(Size(hpbarRect.size.width * progress, hpbarRect.size.height));
		}
		else
		{
			m_hpBar->setVisible(false);
		}
		//Size size = m_sprite->getSpriteFrame()->getOriginalSize();
		//m_hpBar->setPosition(-32, size.height);
	}
}

void CActor::setShowUnitPos(bool isShow)
{
	if (m_unitPos == nullptr)
	{
		m_unitPos = Sprite::createWithSpriteFrameName("GridPos.png");
		CCASSERT(m_unitPos != nullptr, "CActor::setShowUnitPos(): GridPos.png NOT found");

		m_unitPos->setLocalZOrder(0);
		m_layer->addChild(m_unitPos);
	}
	m_unitPos->setVisible(isShow);
}














