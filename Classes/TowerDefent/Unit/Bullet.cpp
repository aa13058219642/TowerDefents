#include "CEffect.h"
#include "Bullet.h"
#include "CActor.h"
//#include "ActorManager.h"
#include "UnitManager.h"
#include "EffectManager.h"
#include "TDUnitCreator.h"
Bullet::Bullet()
{
	m_type = EUnitType::Bullet;
	m_hitEffect = nullptr;
	isTrackTarget = true;
	isFaceToTargetPos = false;

}

Bullet::Bullet(CWeapon* weapon, int parentID, int targetID, Point pos)
{
	//m_type = weapon->BulletType;
	m_type = EUnitType::Bullet;
	isFaceToTargetPos = weapon->IsFaceToTarget;
	isTrackTarget = weapon->IsTrackTarget;
	Speed = weapon->BulletSpeed;
	m_actorName = weapon->ActorName;
	m_parentID = parentID;
	m_targetID.push_back(targetID);
	m_targetPos.push_back(UnitManager::getInstance()->getUnit(targetID)->getPos());
	m_pos = pos;
	m_hitEffect = EffectManager::getInstance()->createHitEffect(weapon, parentID, targetID);
	m_weapon = nullptr;
}


Bullet::~Bullet()
{

}


Bullet* Bullet::clone()
{

	Bullet* bullet = new Bullet();
	bullet->name = this->name;
	bullet->setType(EUnitType::Bullet);
	bullet->setIsTrackTarget(this->isTrackTarget);
	bullet->setIsFaceToTargetPos(this->isFaceToTargetPos);
	bullet->setOnHitEffect(this->m_hitEffect->clone());
	bullet->setActorName(this->m_actorName);
	bullet->Radius = this->Radius;
	bullet->Speed = this->Speed;
	return bullet;
}

void Bullet::update(float dt)
{
	CUnit::update(dt);

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


void Bullet::setTarget(vector<int> targetID)
{
	CUnit::setTarget(targetID);
	if (!isTrackTarget)
	{
		this->m_targetID.clear();
	}
	m_hitEffect->setTarget(targetID[0]);
	m_hitEffect->setParent(ID);
}



void Bullet::setParent(int patentID)
{
	m_parentID = patentID;
}

CUnit* Bullet::getParent()
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
	vector<CUnit*> targets = getTarget();
	if (targets.size() > 0)
	{
		CUnit* target = targets[0];

		if (isTrackTarget == true && target != nullptr)//追踪目标
			m_targetPos[0] = target->getPos();

		Point tpos = m_targetPos[0];
		float dis, move, a;
		dis = m_pos.distance(tpos);
		move = Speed.getValue() *dt;
		a = clampf(move / dis, 0, 1);

		m_pos = a*(tpos - m_pos) + m_pos;
		m_actor->setPos(Point(m_pos.x,m_pos.y-1));

		if (isFaceToTargetPos)
		{
			//方向朝向目标
			float angel = -(tpos - m_pos).getAngle();
			m_actor->setRotation(CC_RADIANS_TO_DEGREES(angel));
		}

		//命中目标
		if (a == 1)
		{
			onHitTarget();
		}
	}

}

void Bullet::onHitTarget()
{
	vector<CUnit*> target = getTarget();

	if (target.size()>0)
	{
		CEffect* effect = m_hitEffect->clone();
		effect->setParent(ID);
		effect->setTarget(target[0]->ID);
		target[0]->addEffect(effect);
	}
	else
	{
		m_hitEffect->execute();
	}

	this->onDead();
}

void Bullet::onDead()
{
	m_actor->setRotation(0);
	//m_sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blank.png"));
	CUnit::onDead();
}



void Bullet::onMissTarget(CUnit* target)
{
	//if (this->target==target){
	//	this->target = nullptr;
	//	this->m_hitEffect->setTarget(-1);
	//}
}

void Bullet::onTargetDead()
{

}


void Bullet::onBindSprite()
{
	m_actor->setLocalLevel(3);
}
