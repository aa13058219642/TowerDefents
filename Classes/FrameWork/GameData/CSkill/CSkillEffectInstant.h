#pragma once
#include "CSkillEffect.h"

namespace cocosgalaxy
{
	class CSkillEffectInstant : public CSkillEffect
	{
	public:

		CSkillEffectInstant();
		~CSkillEffectInstant();

		virtual CSkill* clone();


	};
}

