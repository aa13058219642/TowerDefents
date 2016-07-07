#pragma once
#include "CEffectResponse.h"

class CEffectDamage : public CEffectResponse
{
public:
	CEffectDamage(int damage);
	~CEffectDamage();

	//virtual void Install();
	//virtual void Uninstall();
	virtual CEffect* clone();
	virtual void execute();

	int Damage;

private:


};

