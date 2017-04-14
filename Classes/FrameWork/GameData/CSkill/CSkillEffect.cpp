#include "CSkillEffect.h"
#include "EffectManager.h"
#include "UnitManager.h"
using namespace cocosgalaxy;

CSkillEffect::CSkillEffect()
{
	preparing_Animate = beforing_Animate = using_Animate = aftering_Animate = preparing_Effect = using_Effect = aftering_Effect = "";
	preparing_Delay = beforing_Delay = using_Delay = aftering_Delay = 0;
}


CSkillEffect::~CSkillEffect()
{

}

void CSkillEffect::update(float dt)
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
			if (ColdDowning!=0)break;

		case SkillEffectState_Preparing:
			ColdDowning = preparing_Delay;
			m_parent->setState(EUnitState::UnitState_UsingSkill);
			m_parent->applyAction(preparing_Animate, beforing_Delay);
			if (preparing_Effect != "")
			{
				for (auto i : m_targetID)
				{
					m_parent->addEffect(EffectManager::getInstance()->createCEffect(preparing_Effect, m_parent->ID, i));

				}
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
				for (auto i : m_targetID)
				{
					m_parent->addEffect(EffectManager::getInstance()->createCEffect(using_Effect, m_parent->ID, i));
				}
			}
			m_parent->applyAction(using_Animate, using_Delay);
			m_state = SkillEffectState_Aftering;
			if (ColdDowning != 0)break;

		case SkillEffectState_Aftering:
			ColdDowning = aftering_Delay;
			if (aftering_Effect != "")
			{
				for (auto i : m_targetID)
				{
					m_parent->addEffect(EffectManager::getInstance()->createCEffect(aftering_Effect, m_parent->ID, i));
				}
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



bool CSkillEffect::IsCanExecute()
{
	//至少有一个目标在攻击范围内时，发动技能
	CUnit* m_parent = getParent();
	auto vec = UnitManager::getInstance()->findUnit(Fliter);
	for (auto target : vec)
	{
		if ((target->getPos() - m_parent->getPos()).lengthSquared() < Range*Range)
		{
			m_targetID.push_back(target->ID);
			m_targetPos.push_back(target->getPos());
			return true;
		}
	} 
	return false;
}

