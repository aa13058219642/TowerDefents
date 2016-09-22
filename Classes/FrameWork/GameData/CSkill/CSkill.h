#pragma once
#include "stdfax.h"
#include "Unit.h"



class CSkill
{
public:
	/* ----����---- */

	int ID;
	string name;

	
	/* ----����---- */

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

