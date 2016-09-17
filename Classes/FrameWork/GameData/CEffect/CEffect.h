#pragma once
#include "stdfax.h"
#include "Unit.h"


enum ECEffectState{ 
	ECEffectState_Unused, 
	ECEffectState_Effting, 
	ECEffectState_Death 
};

class CEffect
{
public:

	/* ----属性---- */

	string id;
	float lifetime;
	UnitType filter;

	/* ----方法---- */

	CEffect();
	~CEffect();

	virtual CEffect* clone()=0;
	virtual void execute()=0;
	
	virtual bool Filtered(Unit* obj);	//Unit过滤，通过验证是返回true

	void update(float dt);
	

	virtual void setParent(int parentID);
	virtual Unit* getParent();

	virtual void setTarget(int targetID);
	virtual Unit* getTarget();
	
	void setState(ECEffectState state);
	ECEffectState getState();
	bool isDeath();
protected:
	ECEffectState m_state;
	int m_parentID;
	int m_targetID;

};

