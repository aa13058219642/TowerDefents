#include "Unit.h"
#include "ActorManager.h"
#include "CEffect.h"
#include "CSkill.h"
#include "CBehavior.h"
#include "CBeahaviorBuff.h"

Unit::Unit()
{
	ID = -1;
	m_name = "";
	m_type = EUnitType::Unit_Unit;
	m_state = EUnitState::UnitState_Normal;
	m_pos = Point(0, 0);
	m_actorName = "blank";
	m_weapon = new CWeapon();
	m_actor = nullptr;
	Radius = 32;
}


Unit::~Unit()
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


void Unit::setPos(Point pos)
{
	m_pos = pos;
}

Point Unit::getPos()
{
	return m_pos;
}

void Unit::setType(UnitType type)
{
	m_type |= type;
}

unsigned int Unit::getType()
{
	return m_type;
}

void Unit::setActorName(Name actorName)
{
	m_actorName = actorName;
}

void Unit::setState(EUnitState state)
{
	m_state = state;
}

EUnitState Unit::getState()
{
	return m_state;
}

void Unit::setWeapon(CWeapon* weapon)
{
	if (m_weapon != nullptr)delete m_weapon;
	m_weapon = weapon;
}

CWeapon* Unit::getWeapon()
{
	return m_weapon;
}



void Unit::bindActor()
{
	m_actor = ActorManager::getInstance()->createActor(ID, m_actorName);
	CCASSERT(m_actor != nullptr, "Actor bind fail!");
	m_actor->setPos(m_pos);
	onBindSprite();
}

bool Unit::isClickMe(Point pos)
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

void Unit::update(float dt)
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


void Unit::onClick(){};
void Unit::onBindSprite(){}
void Unit::onAttack(Unit* target){}
void Unit::onBeAttack(int damage, EDamageType damageType){}
void Unit::onMove(){}
void Unit::onHitTarget(){}
void Unit::onMissTarget(Unit* target){}

void Unit::onDead(){ 
	m_type |= Unit_Death;
	ActorManager::getInstance()->removeActor(ID);
	onDeaded();
}

void Unit::onDeaded()
{
	m_type |= Unit_Destory;
}




void Unit::addEffect(CEffect* effect)
{
	if (effect!=nullptr)
		effects.push_back(effect);
}

void Unit::addSkill(CSkill* skill)
{
	if (skill != nullptr)
		skills.push_back(skill);
}


void Unit::addBehavior(CBehavior* behavior)
{
	if (behavior != nullptr)
	{
		m_behaviors.push_back(behavior);
		behavior->Install(this);
		//updateModification();
	}

}

void Unit::updateModification()
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

void Unit::applyAction(Name actionName, float playtime)
{
	if (!actionName.empty())
		m_actor->playAction(actionName, playtime);
}

void Unit::applyAEffect(Name effectName, float playtime)
{
	if (!effectName.empty())
		m_actor->playEffect(effectName, playtime);
}





void Unit::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 1, 1, 0.3F), 1.0F, Color4F(1, 1, 1, 1));
}
