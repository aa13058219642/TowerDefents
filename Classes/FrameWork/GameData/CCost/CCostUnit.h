#pragma once
#include "Ability.h"
#include "CCost.h"
class Unit;

class CCostUnit : public CCost
{
public:
	CCostUnit();
	~CCostUnit();

	virtual bool isCanPay(Unit* parent);
	virtual void payCost(Unit* parent);

	Ability<float> HP;
	Ability<float> MP;
	Ability<float> AP;
	Ability<float> Speed;



//private:
};

