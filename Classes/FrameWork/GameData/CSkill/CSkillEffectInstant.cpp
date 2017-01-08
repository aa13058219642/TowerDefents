#include "CSkillEffectInstant.h"
using namespace cocosgalaxy;

CSkillEffectInstant::CSkillEffectInstant()
{
	m_type = ESkillType::ECSkillEffectInstant;
}


CSkillEffectInstant::~CSkillEffectInstant()
{

}



CSkill* CSkillEffectInstant::clone()
{
	CSkillEffectInstant* skill = new CSkillEffectInstant();
	skill->name = this->name;
	skill->m_state = this->m_state;
	skill->ColdDown = this->ColdDown;
	skill->ColdDowning = this->ColdDowning;
	skill->Range = this->Range;
	skill->AutoUseRange = this->AutoUseRange;
	skill->Cost = this->Cost;
	skill->chance = this->chance;
	skill->Fliter = this->Fliter;

	skill->preparing_Animate = this->preparing_Animate;
	skill->beforing_Animate = this->beforing_Animate;
	skill->using_Animate = this->using_Animate;
	skill->aftering_Animate = this->aftering_Animate;
	skill->preparing_Effect = this->preparing_Effect;
	skill->using_Effect = this->using_Effect;
	skill->aftering_Effect = this->aftering_Effect;
	skill->preparing_Delay = this->preparing_Delay;
	skill->beforing_Delay = this->beforing_Delay;
	skill->using_Delay = this->using_Delay;
	skill->aftering_Delay = this->aftering_Delay;

	return skill;
}






