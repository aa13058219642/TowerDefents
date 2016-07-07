#pragma once
#include "CEffect.h"

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

	std::list<CEffect*> getEffects();

private:
	std::list<CEffect*> effects;

};

