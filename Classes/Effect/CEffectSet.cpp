#include "CEffectSet.h"

CEffectSet::CEffectSet()
{

}


CEffectSet::~CEffectSet()
{

}
void CEffectSet::execute(){}

CEffect* CEffectSet::clone()
{
	CEffectSet* effect = new CEffectSet();
	return effect;
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