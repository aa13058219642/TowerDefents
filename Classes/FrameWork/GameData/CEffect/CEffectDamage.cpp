#include "CEffectDamage.h"
#include "GalaxyHelper.h"
using namespace cocosgalaxy;

CEffectDamage::CEffectDamage()
{
	this->minDamage = 0;
	this->maxDamage = 0;
	this->damageType = EDamageType::EDamageType_Weapon;
	this->effectAnimate = "";
	this->m_parentID = -1;
	this->m_targetID = -1;
}


CEffectDamage::CEffectDamage(float minDamage, float maxDamage, EDamageType damageType, Name effectAnimate, int parentID, int targetID)
{
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->damageType = damageType;
	this->effectAnimate = effectAnimate;
	this->m_parentID = parentID;
	this->m_targetID = targetID;
}


CEffectDamage::~CEffectDamage()
{

}

void CEffectDamage::execute()
{
	CUnit* target = getTarget();
	if (target != nullptr)
	{
		target->onBeAttack(helper::rand(minDamage, maxDamage), damageType);
		target->applyAEffect(effectAnimate);
	}

	this->setState(ECEffectState::ECEffectState_Death);


}

CEffect* CEffectDamage::clone()
{
	CEffectDamage* effect = new CEffectDamage(minDamage, maxDamage, damageType, effectAnimate);
	return effect;
}
