#pragma once
#include "CSkillGeneric.h"
#include "CWeapon.h"

class CSkillAttactk :public CSkillGeneric
{
public:
	CSkillAttactk();
	~CSkillAttactk();

	virtual void update(float dt);
	virtual bool IsCanExecute();
	virtual CSkill* clone();
protected:
	CWeapon* m_weapon;

	int m_targetID;
	Point m_targetPos;

	void onAttack(Unit* parent);
};

