#include "CSkillGeneric.h"
#include "UnitManager.h"

CSkillGeneric::CSkillGeneric()
{
	m_type = ESkillType::ECSkillEffect;
	Fliter = EUnitType::Unit_Unit;
	m_state = ESkillEffectState::SkillEffectState_ColdDowning;
	Range = AutoUseRange = 0;
	chance = 1;
}


CSkillGeneric::~CSkillGeneric()
{

}







