#include "CEffect.h"
#include "UnitManager.h"

CEffect::CEffect()
{
	lifetime = 0;
	m_parentID = m_targetID = -1;
	m_state = ECEffectState::ECEffectState_Unused;
}


CEffect::~CEffect()
{

}

void CEffect::setParent(int parentID)
{
	this->m_parentID = parentID;
}

Unit* CEffect::getParent()
{
	return UnitManager::getInstance()->getUnit(m_parentID);
}

void CEffect::setTarget(int targetID)
{
	this->m_targetID = targetID;
}

Unit* CEffect::getTarget()
{
	return UnitManager::getInstance()->getUnit(m_targetID);
}


void CEffect::update(float dt)
{
	lifetime -= dt;
	if (lifetime <= 0)
	{
		m_state = ECEffectState::ECEffectState_Effting;
		this->execute();
	}
}

bool CEffect::Filtered(Unit* obj)
{
	//ÈôA U B = A ÔòBº¬ÓÚA
	if ((obj->getType() | filter) == filter){
		return true;
	}
	return false;
}

void CEffect::setState(ECEffectState state)
{
	m_state = state;
}

ECEffectState CEffect::getState()
{
	return m_state;
}

bool CEffect::isDeath()
{
	return m_state == ECEffectState::ECEffectState_Death ? true : false;
}



