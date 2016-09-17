#pragma once
#include "CSkill.h"

class CSkillGeneric :public CSkill
{
public:
	/* ----属性---- */

	/*冷却时间*/
	float ColdDown;
	/*冷却时间剩余*/
	float ColdDowning;
	/*技能花费*/
	SkillCost Cost;
	/*射程*/
	float Range;
	/*目标筛选器*/
	UnitType Fliter;
	/*自动施放范围 0=不自动施放*/
	float AutoUseRange;
	/*成功率*/
	float chance;

	/* ----方法---- */

	CSkillGeneric();
	~CSkillGeneric();
protected:
	ESkillEffectState m_state;
};

