#include "CEffectResponse.h"

CEffectResponse::CEffectResponse()
{
	lifetime = 0;
}


CEffectResponse::~CEffectResponse()
{

}

void CEffectResponse::execute(){}

CEffect* CEffectResponse::clone()
{
	CEffectResponse* effect = new CEffectResponse();
	return effect;
}
//void CEffectSet::updateLifeTime(float dt)
//{
//	lifetime -= dt;
//	if (lifetime <= 0){
//		Uninstall();
//	}
//
//}