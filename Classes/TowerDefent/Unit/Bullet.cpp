#include "CEffect.h"
#include "Bullet.h"
#include "Actor.h"
//#include "ActorManager.h"
#include "UnitManager.h"
#include "EffectManager.h"

Bullet::Bullet()
{
	m_targetID = -1;
	m_type = EUnitType::Unit_Bullet;
	m_targetPos = Point::ZERO;
	m_hitEffect = nullptr;
	isTrackTarget = true;
	isFaceToTargetPos = false;

}

Bullet::Bullet(CWeapon* weapon, int parentID, int targetID, Point pos)
{
	//m_type = weapon->BulletType;
	m_type = EUnitType::Unit_Bullet;
	isFaceToTargetPos = weapon->IsFaceToTarget;
	isTrackTarget = weapon->IsTrackTarget;
	Speed = weapon->BulletSpeed;
	m_actorName = weapon->ActorName;
	m_parentID = parentID;
	m_targetID = targetID;
	m_pos = pos;
	//m_hitEffect = weapon.createHitEffect(parentID, targetID);
	m_weapon = new CWeapon(*weapon);
}


Bullet::~Bullet()
{

}


Bullet* Bullet::clone()
{

	Bullet* bullet = new Bullet();
	bullet->setType(EUnitType::Unit_Bullet);
	bullet->setIsTrackTarget(this->isTrackTarget);
	bullet->setIsFaceToTargetPos(this->isFaceToTargetPos);
	bullet->setOnHitEffect(this->m_hitEffect->clone());
	bullet->setActorName(this->m_actorName);

	return bullet;
}

void Bullet::update(float dt)
{
	Unit::update(dt);

	onMove(dt);
}


void Bullet::drawMyOutLine(DrawNode* drawNode)
{
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 1, 1, 0.3F), 1.0F, Color4F(1, 1, 1, 1));
}


void Bullet::setTarget(int targetID)
{
	if (isTrackTarget)
	{
		this->m_targetID = targetID;
	}
	else
	{
		this->m_targetID = -1;
	}
	m_hitEffect->setTarget(targetID);
	m_hitEffect->setParent(ID);
	this->m_targetPos = UnitManager::getInstance()->getUnit(targetID)->getPos();

}

Unit* Bullet::getTarget()
{
	return UnitManager::getInstance()->getUnit(m_targetID);
}

void Bullet::setParent(int patentID)
{
	m_parentID = patentID;
}

Unit* Bullet::getParent()
{
	return UnitManager::getInstance()->getUnit(m_parentID);
}


void Bullet::setIsTrackTarget(bool IsTrackTarget)
{
	isTrackTarget = IsTrackTarget;
}

void Bullet::setIsFaceToTargetPos(bool IsFaceToTargetPos)
{
	isFaceToTargetPos = IsFaceToTargetPos;

}

void Bullet::setOnHitEffect(CEffect* effect)
{
	m_hitEffect = effect;
}


void Bullet::onMove(float dt)
{
	Unit* target = getTarget();

	if (isTrackTarget == true && target != nullptr)//追踪目标
		m_targetPos = target->getPos();

	float dis, move, a;
	dis = m_pos.distance(m_targetPos);
	if (dis > 0){
		move = Speed.getValue() *dt;
		a = move / dis;
		if (a < 1){
			m_pos = a*(m_targetPos - m_pos) + m_pos;
			m_actor->setPos(Point(m_pos.x,m_pos.y+1));

			if (isFaceToTargetPos)
			{
				//方向朝向目标
				float angel = -(m_targetPos - m_pos).getAngle();
				m_actor->setRotation(CC_RADIANS_TO_DEGREES(angel));
			}
			return;
		}
	}
	onHitTarget();
}

void Bullet::onHitTarget()
{
	Unit* target = getTarget();

	if (target != nullptr){
		target->addEffect(EffectManager::getInstance()->createHitEffect(m_weapon,ID, m_targetID));
	}
	else
	{
		EffectManager::getInstance()->createHitEffect(m_weapon, ID, m_targetID)->execute();
	}

	this->onDead();
}

void Bullet::onDead()
{
	m_actor->setRotation(0);
	//m_sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blank.png"));
	Unit::onDead();
}



void Bullet::onMissTarget(Unit* target)
{
	//if (this->target==target){
	//	this->target = nullptr;
	//	this->m_hitEffect->setTarget(-1);
	//}
}

void Bullet::onTargetDead()
{

}



