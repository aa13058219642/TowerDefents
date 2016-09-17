#pragma once
#include "stdfax.h"
#include "Unit.h"


struct SkillCost
{
	float HP = 0;
	float MP = 0;
	int money = 0;

};

class CSkill
{
public:
	/* ---- Ù–‘---- */

	int ID;
	string name;

	
	/* ----∑Ω∑®---- */

	CSkill();
	~CSkill();
	virtual CSkill* clone() = 0;

	void setType(ESkillType type);
	ESkillType getType();

	void setParent(int parentID);
	Unit* getParent();

	virtual void update(float dt) = 0;
	virtual bool IsCanExecute() = 0;

protected:
	string groupID;
	ESkillType m_type;
	int m_parentID;
};

