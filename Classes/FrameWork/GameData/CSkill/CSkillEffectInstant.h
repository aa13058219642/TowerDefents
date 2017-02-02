#pragma once
#include "CSkillEffect.h"

namespace cocosgalaxy
{
	class CSkillEffectInstant : public CSkillEffect
	{
	public:

		CSkillEffectInstant();
		~CSkillEffectInstant();

		virtual void update(float dt);
		virtual CSkill* clone();

		void applyEffect(string effectName);
	};
}

