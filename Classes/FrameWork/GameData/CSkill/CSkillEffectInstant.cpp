#include "CSkillEffectInstant.h"
#include "EffectManager.h"
#include "UnitManager.h"
using namespace cocosgalaxy;

CSkillEffectInstant::CSkillEffectInstant()
{
	m_type = ESkillType::ECSkillEffectInstant;
}


CSkillEffectInstant::~CSkillEffectInstant()
{

}


void CSkillEffectInstant::update(float dt)
{
	CUnit* m_parent = getParent();
	if (m_parent == nullptr)return;

	if (ColdDowning > dt)
		ColdDowning -= dt;
	else
	{
		switch (m_state)
		{
		case SkillEffectState_ColdDowning:
			ColdDowning = 0;
			m_state = SkillEffectState_Ready;
			break;

		case SkillEffectState_Ready:
			//使用技能的条件
			if (m_parent->getState() == EUnitState::UnitState_Normal && AutoUseRange > 0 && IsCanExecute())
			{
				//成功率判断
				if (chance == 1 || rand_0_1() <= chance)
				{
					m_parent->setState(EUnitState::UnitState_UsingSkill);
					m_state = SkillEffectState_Approaching;
				}
				else
					m_state = SkillEffectState_End;
			}
			break;

		case SkillEffectState_Approaching:
			ColdDowning = 0;
			m_state = SkillEffectState_Preparing;
			if (ColdDowning != 0)break;

		case SkillEffectState_Preparing:
			ColdDowning = preparing_Delay;
			m_parent->setState(EUnitState::UnitState_UsingSkill);
			m_parent->applyAction(preparing_Animate, beforing_Delay);
			if (preparing_Effect != "")
			{
				applyEffect(preparing_Effect);
			}
			m_state = SkillEffectState_Beforing;
			if (ColdDowning != 0)break;

		case SkillEffectState_Beforing:
			ColdDowning = beforing_Delay;
			m_parent->applyAction(beforing_Animate, beforing_Delay);
			m_state = SkillEffectState_Using;
			if (ColdDowning != 0)break;

		case SkillEffectState_Using:
			ColdDowning = using_Delay;
			if (using_Effect != "")
			{
				applyEffect(using_Effect);
			}
			m_parent->applyAction(using_Animate, using_Delay);
			m_state = SkillEffectState_Aftering;
			if (ColdDowning != 0)break;

		case SkillEffectState_Aftering:
			ColdDowning = aftering_Delay;
			if (aftering_Effect != "")
			{
				applyEffect(aftering_Effect);
			}
			m_parent->applyAction(aftering_Animate, aftering_Delay);
			m_state = SkillEffectState_End;
			if (ColdDowning != 0)break;

		case SkillEffectState_End:
			ColdDowning = ColdDown;
			m_parent->setState(EUnitState::UnitState_Normal);
			m_state = SkillEffectState_ColdDowning;
			if (ColdDowning != 0)break;
		default:
			break;
		}
	}
}

void CSkillEffectInstant::applyEffect(string effectName)
{
	CUnit* target = UnitManager::getInstance()->getUnit(m_targetID[0]);
	//如果失去目标，原来锁定的目标在前摇时跑出了攻击范围，则强制攻击一开始锁定的目标
	if (target == nullptr)
	{
		if (IsCanExecute())
		{
			EffectManager::getInstance()->createCEffect(aftering_Effect, m_parentID, target->ID)->execute();
		}
	}
	else
	{
		EffectManager::getInstance()->createCEffect(aftering_Effect, m_parentID, target->ID)->execute();
	}
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






