#pragma once
#include "CEffect.h"

namespace cocosgalaxy
{
	class CEffectSet : public CEffect
	{
	public:
		CEffectSet();
		~CEffectSet();

		//virtual void Install();
		//virtual void Uninstall();
		//void updateLifeTime(float dt);
		virtual CEffect* clone();
		virtual void execute();

		virtual void setParent(int parentID);
		virtual void setTarget(int targetID);

		std::list<CEffect*> getEffects();
		void addEffect(CEffect* effect);
	private:
		std::list<CEffect*> effects;

	};

}