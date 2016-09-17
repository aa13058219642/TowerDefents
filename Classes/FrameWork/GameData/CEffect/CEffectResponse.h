#pragma once
#include "CEffect.h"

class CEffectResponse : public CEffect
{
public:
	CEffectResponse();
	~CEffectResponse();

	virtual CEffect* clone()=0;
	virtual void execute()=0;


	float chance;	//发动几率
private:


};

