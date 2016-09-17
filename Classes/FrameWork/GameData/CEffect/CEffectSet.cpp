#include "CEffectSet.h"

CEffectSet::CEffectSet()
{

}


CEffectSet::~CEffectSet()
{
	if (!effects.empty())
	{
		for (auto var : effects){
			delete var;
		}
	}
	effects.clear();
}

void CEffectSet::setParent(int parentID)
{
	this->m_parentID = parentID;
	for (auto var : effects)
		var->setParent(parentID);
}

void CEffectSet::setTarget(int targetID)
{
	this->m_targetID = targetID;
	for (auto var : effects)
		var->setTarget(targetID);
}

void CEffectSet::execute()
{
	if (!effects.empty())
	{
		for (auto var : effects){
			var->execute();
		}
	}
	this->setState(ECEffectState::ECEffectState_Death);
}

CEffect* CEffectSet::clone()
{
	CEffectSet* effect = new CEffectSet();
	for (auto var : effects)
		effect->addEffect(var->clone());
	return effect;
}

void CEffectSet::addEffect(CEffect* effect)
{
	effects.push_back(effect);
}



std::list<CEffect*> CEffectSet::getEffects()
{
	return effects;
}

//void CEffectSet::updateLifeTime(float dt)
//{
//	lifetime -= dt;
//	if (lifetime <= 0){
//		Uninstall();
//	}
//
//}