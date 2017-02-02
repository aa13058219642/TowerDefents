#pragma once
#include "CEffectResponse.h"

namespace cocosgalaxy
{
	class CEffectDamage : public CEffectResponse
	{
	public:
		CEffectDamage();
		CEffectDamage(float minDamage, float maxDamage, EDamageType damageType = EDamageType::EDamageType_Weapon, Name effectAnimate = "", int parentID = -1, int targetID = -1);
		~CEffectDamage();

		virtual CEffect* clone();
		virtual void execute();


		float minDamage;			//最小伤害
		float maxDamage;			//最大伤害
		EDamageType damageType;	//伤害类型
		Name effectAnimate;		//效果动画
	private:


	};
}
