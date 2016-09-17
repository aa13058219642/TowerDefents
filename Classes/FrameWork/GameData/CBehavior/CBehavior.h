#pragma once
#include "stdfax.h"
#include "CCost.h"
#include "Unit.h"


enum EBehaviorType{
	ECBehavior,
	ECBeahaviorBuff
};

class CBehavior
{
public:
	int id;
	Name name;
	CCost cost;
	//Requirement
	

enum EBehaviorState{
	EBehaviorState_Unused,
	EBehaviorState_Using,
	EBehaviorState_Death
};

	CBehavior();
	~CBehavior();

	virtual CBehavior* clone() = 0;
	virtual bool meetRequirement() = 0;
	virtual void Install(Unit* parent) = 0;
	virtual void Uninstall(Unit* parent) = 0;
	virtual void update(float dt) = 0;

	//void setParent(Unit* parent);
	EBehaviorType getType();
	bool isDeath();
protected:
	EBehaviorType m_type;
	EBehaviorState m_state;
	Unit* m_parent;
};

