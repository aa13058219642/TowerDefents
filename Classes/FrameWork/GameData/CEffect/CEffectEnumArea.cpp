#include "CEffectEnumArea.h"
#include "EffectManager.h"
#include "UnitManager.h"

CEffectEnumArea::CEffectEnumArea(unsigned int filter, int areaRadius, string applyEffect, CEffect* effect, int parentID)
{
	this->filter = filter;
	this->areaRadius = areaRadius;
	this->applyEffect = applyEffect;
	this->effect = effect;
	this->m_parentID = parentID;
	this->m_pos = getParent()->getPos();
}



CEffectEnumArea::~CEffectEnumArea()
{
	if (effect != nullptr)
		delete effect;
}

void CEffectEnumArea::execute()
{
	Unit* m_parent = getParent();
	if (m_parent != nullptr)m_pos = getParent()->getPos();

	if (effect != nullptr)
	{
		for (auto var : UnitManager::getInstance()->findUnit(filter))
			if (var->getPos().distanceSquared(m_pos) <= areaRadius*areaRadius)
			{
				CEffect* efc = effect->clone();
				efc->setParent(var->ID);
				efc->setTarget(var->ID);
				var->addEffect(efc);
			}
	}
	else{
		for (auto var : UnitManager::getInstance()->findUnit(filter))
			if (var->getPos().distanceSquared(m_pos) <= areaRadius*areaRadius)
				var->addEffect(EffectManager::getInstance()->createCEffect(applyEffect, var->ID, var->ID));
	}

	this->setState(ECEffectState::ECEffectState_Death);

}


CEffect* CEffectEnumArea::clone()
{
	if (effect == nullptr)
		return new CEffectEnumArea(filter, areaRadius, applyEffect);
	else
		return new CEffectEnumArea(filter, areaRadius, applyEffect, effect->clone());
}
