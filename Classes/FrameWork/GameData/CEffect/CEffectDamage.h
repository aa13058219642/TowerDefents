#pragma once
#include "CEffectResponse.h"


class CEffectDamage : public CEffectResponse
{
public:
	CEffectDamage(float minDamage, float maxDamage, EDamageType damageType = EDamageType::EDamageType_Weapon, Name effectAnimate = "", int parentID = -1, int targetID = -1);
	~CEffectDamage();

	virtual CEffect* clone();
	virtual void execute();


private:
	float m_MinDamage;
	float m_MaxDamage;
	EDamageType m_damageType;
	Name m_effectAnimate;


};

