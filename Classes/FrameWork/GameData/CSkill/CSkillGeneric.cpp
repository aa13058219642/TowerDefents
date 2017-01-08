#include "CSkillGeneric.h"
using namespace cocosgalaxy;

CSkillGeneric::CSkillGeneric()
{
	m_type = ESkillType::ECSkillEffect;
	Fliter = EUnitType::Unit;
	m_state = ESkillEffectState::SkillEffectState_ColdDowning;
	Range = AutoUseRange = 0;
	chance = 1;
}


CSkillGeneric::~CSkillGeneric()
{

}







