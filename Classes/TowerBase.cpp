#include "TowerBase.h"
#include "GameObjectLayer.h"
#include "BulletFactory.h"
#include "EffectManager.h"

TowerBase::TowerBase()
{
	level = 0;
}


TowerBase::~TowerBase()
{

}


TowerBase* TowerBase::create(Point pos, bool isDebug)
{
	TowerBase* towerBase = new TowerBase();
	if (towerBase && towerBase->init(pos, isDebug))
	{
		towerBase->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(towerBase);
	}
	return towerBase;
}


bool TowerBase::init(Point pos, bool isDebug)
{
	bool flag = false;
	
	do{
		setPos(pos);
		setPosition(pos);

		flag = true;
	} while (0);

	return flag;
}


GameObjectType TowerBase::getObjectType()
{
	return GameObjectType::GameObject_Tower;
}


void TowerBase::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[1] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[2] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y - cur_ability.Radius);
	point[3] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y - cur_ability.Radius);

	drawNode->drawPolygon(point, 4, Color4F(0, 1, 0, level / 5.0), 1, Color4F(0, 1, 0, 1));
}

void TowerBase::upgrade()
{
	//this->unschedule(schedule_selector(TowerBase::onAttack));
	if (level == 0)
	{
		m_ability.Radius = 32;
		m_ability.Range = 200;
		m_ability.Reload = 1.0;
		cur_ability = m_ability;
		std::string file = StringUtils::format("tower/tower_%d.png", 1);
		auto sprite = Sprite::create(file);
		////sprite->runAction(ActionManager::)
		sprite->setPosition(0, -m_ability.Radius);
		sprite->setAnchorPoint(Point(0.5, 0));
		this->bindSprite(sprite);
		level++;
	}
	else if (level<5){
		m_ability.Range += 200;
		m_ability.Reload -= 0.12f;
		if (m_ability.Reload < 0.1)
			m_ability.Reload = 0.1f;
		cur_ability = m_ability;
		std::string file = StringUtils::format("tower/tower_%d.png", 2);
		auto sprite = Sprite::create(file);
		sprite->setPosition(0, -m_ability.Radius);
		sprite->setAnchorPoint(Point(0.5, 0));

		////sprite->runAction(ActionManager::)
		this->bindSprite(sprite);
		level++;
	}
	else{

	}


	this->schedule(schedule_selector(TowerBase::onAttack), cur_ability.Reload);
}


void TowerBase::onAttack(float dt)
{
	GameObjectLayer* parent = (GameObjectLayer*)getParent();
	for (auto monster : parent->gameObjectList){
		if (monster->getObjectType()==GameObjectType::GameObject_Monster && (monster->getPos() - m_pos).lengthSquared() < cur_ability.Range*cur_ability.Range)
		{
			CEffect* effect = EffectManager::getInstance()->createCEffect("LaunchMissile", this, monster);
			effect->execute();
			//Bullet* bullet = BulletFactory::getInstance()->CreateBullet(1, m_pos, monster);
			//bullet->addToParents(parent);
			//parent->gameObjectList.pushBack(bullet);
			//parent->addChild(bullet);
			return;
		}
	}
}