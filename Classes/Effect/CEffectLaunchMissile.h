#pragma once
#include "CEffectResponse.h"

class CEffectLaunchMissile : public CEffectResponse
{
public:
	CEffectLaunchMissile(int BulletID);
	~CEffectLaunchMissile();

	//virtual void Install();
	//virtual void Uninstall();
	virtual CEffect* clone();
	virtual void execute();



private:
	int BulletID;

};

