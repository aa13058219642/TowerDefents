#pragma once
#include "CSkillEffect.h"

class CSkillEffectInstant : public CSkillEffect
{
public:
	/*冷却时间*/
	float ColdDown;
	/*冷却时间剩余*/
	float ColdDowning;

	CSkillEffectInstant();
	~CSkillEffectInstant();

	virtual CSkill* clone();


};

