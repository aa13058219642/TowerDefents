#include "CUnit.h"
#include "CModification.h"
#include "CWeapon.h"
#include "CActor.h"
#include "CBehavior.h"
#include "CEffect.h"
#include "CSkill.h"
#include "ActorManager.h"
#include "UnitManager.h"
using namespace cocosgalaxy;

CUnit::CUnit()
{
	ID = -1;
	m_name = "";
	m_type = EUnitType::Unit;
	m_state = EUnitState::UnitState_Normal;
	m_pos = Point(0, 0);
	m_actorName = "blank";
	m_weapon = new CWeapon();
	m_actor = nullptr;
	Radius = 32;

}


CUnit::~CUnit()
{
	if (!effects.empty())
	{
		for (auto var : effects){
			delete var;
		}
	}
	effects.clear();

	if (!skills.empty())
	{
		for (auto var : skills){
			delete var;
		}
	}
	skills.clear();

	if (m_weapon != nullptr)delete m_weapon;

}


void CUnit::setPos(Point pos)
{
	m_pos = pos;
}

Point CUnit::getPos()
{
	return m_pos;
}

void CUnit::setType(UnitType type)
{
	m_type |= type;
}

unsigned int CUnit::getType()
{
	return m_type;
}

void CUnit::setActorName(Name actorName)
{
	m_actorName = actorName;
}

void CUnit::setState(EUnitState state)
{
	m_state = state;
}

EUnitState CUnit::getState()
{
	return m_state;
}

void CUnit::setWeapon(CWeapon* weapon)
{
	if (m_weapon != nullptr)delete m_weapon;
	m_weapon = weapon;
}

CWeapon* CUnit::getWeapon()
{
	return m_weapon;
}

void CUnit::setTarget(int targetID)
{
	this->m_targetID = targetID;
	this->m_targetPos = UnitManager::getInstance()->getUnit(targetID)->getPos();
}

CUnit* CUnit::getTarget()
{
	return UnitManager::getInstance()->getUnit(m_targetID);
}

void CUnit::bindActor()
{
	m_actor = ActorManager::getInstance()->createActor(ID, m_actorName);
	CCASSERT(m_actor != nullptr, "CActor bind fail!");
	m_actor->setPos(m_pos);
	onBindSprite();
}

bool CUnit::isClickMe(Point pos)
{
	Point srcPos, descPos;

	srcPos = Point(m_pos.x - Radius, m_pos.y + Radius);
	descPos = Point(m_pos.x + Radius, m_pos.y - Radius);
	if (pos.x >= srcPos.x &&
		pos.x <= descPos.x &&
		pos.y <= srcPos.y &&
		pos.y >= descPos.y){
		return true;
	}
	return false;
}

void CUnit::update(float dt)
{
	//update Skill
	for (auto var : skills){
		var->update(dt);
	}

	//update Effect
	for (auto var : effects){
		var->update(dt);
	}

	//remove Executed Effect
	for (auto iter = effects.begin(); iter != effects.end();)
	{
		CEffect* var = *iter;
		if (var->isDeath())
		{
			delete var;
			iter = effects.erase(iter);
		}
		else
			iter++;
	}

	//update Behavior
	for (auto var : m_behaviors){
		var->update(dt);
	}



	//remove Executed Effect
	for (auto iter = m_behaviors.begin(); iter != m_behaviors.end();)
	{
		CBehavior* var = *iter;
		if (var->isDeath())
		{
			delete var;
			iter = m_behaviors.erase(iter);
		}
		else
			iter++;
	}



}


void CUnit::onClick(){};
void CUnit::onBindSprite(){}
void CUnit::onAttack(CUnit* target){}
void CUnit::onBeAttack(int damage, EDamageType damageType){}
void CUnit::onMove(){}
void CUnit::onHitTarget(){}
void CUnit::onMissTarget(CUnit* target){}

void CUnit::onDead(){ 
	m_type |= EUnitType::Death;
	ActorManager::getInstance()->removeActor(ID);
	onDeaded();
}

void CUnit::onDeaded()
{
	m_type |= EUnitType::Destory;
}




void CUnit::addEffect(CEffect* effect)
{
	if (effect!=nullptr)
		effects.push_back(effect);
}

void CUnit::addSkill(CSkill* skill)
{
	if (skill != nullptr)
		skills.push_back(skill);
}


void CUnit::addBehavior(CBehavior* behavior)
{
	if (behavior != nullptr)
	{
		m_behaviors.push_back(behavior);
		behavior->Install(this);
		//updateModification();
	}

}

void CUnit::updateModification()
{
	//m_modification.clear();
	//for (auto var : m_behaviors)
	//{
	//	if (var->getType() == EBehaviorType::ECBeahaviorBuff)
	//	{
	//		CBeahaviorBuff* buf = static_cast<CBeahaviorBuff*>(var);
	//		m_modification.merge(buf->m_modList);
	//	}
	//}
	//m_modification.sort();

	//for (auto& var : m_modification)
	//{
	//	var.installModification(this);
	//}
	//m_modification



}

void CUnit::applyAction(Name actionName, float playtime)
{
	if (!actionName.empty())
		m_actor->playAction(actionName, playtime);
}

void CUnit::applyAEffect(Name effectName, float playtime)
{
	if (!effectName.empty())
		m_actor->playEffect(effectName, playtime);
}





void CUnit::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 1, 1, 0.3F), 1.0F, Color4F(1, 1, 1, 1));
}