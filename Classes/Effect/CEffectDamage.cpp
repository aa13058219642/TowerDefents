#include "CEffectDamage.h"

CEffectDamage::CEffectDamage(int damage)
{
	this->Damage = damage;
}


CEffectDamage::~CEffectDamage()
{

}

void CEffectDamage::execute()
{
	m_target->onBeAttack(this->Damage);
}

CEffect* CEffectDamage::clone()
{
	CEffectDamage* effect = new CEffectDamage(this->Damage);
	return effect;
}
//void CEffectDamage::Install()
//{
//}
//
//
//
//void CEffectDamage::Uninstall()
//{
//
//}

//void CEffectSet::updateLifeTime(float dt)
//{
//	lifetime -= dt;
//	if (lifetime <= 0){
//		Uninstall();
//	}
//
//}