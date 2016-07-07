#pragma once
#include "CEffect.h"

class CEffectResponse : public CEffect
{
public:
	CEffectResponse();
	~CEffectResponse();

	//virtual void Install();
	//virtual void Uninstall();
	virtual CEffect* clone();
	virtual void execute();


	float chance;	//发动几率
private:


};

