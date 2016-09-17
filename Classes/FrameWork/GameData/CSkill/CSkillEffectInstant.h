#pragma once
#include "CSkillEffect.h"

class CSkillEffectInstant : public CSkillEffect
{
public:
	CSkillEffectInstant();
	~CSkillEffectInstant();

	virtual CSkill* clone();


};

