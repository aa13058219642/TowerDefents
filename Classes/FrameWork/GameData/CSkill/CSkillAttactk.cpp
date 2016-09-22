#include "CSkillAttactk.h"
#include "EffectManager.h"
#include "UnitManager.h"
#include "Bullet.h"

CSkillAttactk::CSkillAttactk()
{
	m_weapon = nullptr;
	m_targetID = -1;
	m_targetPos = Point::ZERO;
}


CSkillAttactk::~CSkillAttactk()
{

}

CSkill* CSkillAttactk::clone()
{
	CSkillAttactk* skill = new CSkillAttactk();
	skill->m_state = this->m_state;
	skill->ColdDown = this->ColdDown;
	skill->ColdDowning = this->ColdDowning;
	skill->Range = this->Range;
	skill->AutoUseRange = this->AutoUseRange;
	skill->Cost = this->Cost;
	skill->chance = this->chance;
	skill->Fliter = this->Fliter;

	return skill;
}


void CSkillAttactk::UpdateCWeapon()
{
	m_weapon = getParent()->getWeapon();
	ColdDown = m_weapon->ColdDown;
}

void CSkillAttactk::update(float dt)
{
	Unit* m_parent = getParent();
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
			UpdateCWeapon();
			//使用技能的条件
			if (m_parent->getState() == EUnitState::UnitState_Normal && IsCanExecute())
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
			m_state = SkillEffectState_Beforing;
			if (ColdDowning != 0)break;

		case SkillEffectState_Beforing:
			ColdDowning = m_weapon->beforing_Delay;
			m_parent->applyAction(m_weapon->beforing_Animate, m_weapon->beforing_Delay);
			m_state = SkillEffectState_Using;
			if (ColdDowning != 0)break;

		case SkillEffectState_Using:
			ColdDowning = m_weapon->using_Delay;
			this->onAttack(m_parent);//onAttack
			m_parent->applyAction(m_weapon->using_Animate, m_weapon->using_Delay);
			m_state = SkillEffectState_Aftering;
			if (ColdDowning != 0)break;
			       
		case SkillEffectState_Aftering:
			ColdDowning = m_weapon->aftering_Delay;
			m_parent->applyAction(m_weapon->aftering_Animate, m_weapon->aftering_Delay);
			m_state = SkillEffectState_End;
			if (ColdDowning != 0)break;

		case SkillEffectState_End:
			ColdDowning = ColdDown;
			m_parent->setState(EUnitState::UnitState_Normal);
			m_state = SkillEffectState_ColdDowning;
			m_targetID = -1;
			m_targetPos = Point::ZERO;
			if (ColdDowning != 0)break;
		default:
			break;
		}
	}
}


bool CSkillAttactk::IsCanExecute()
{
	int targetCount = m_weapon->TargetCount;
	if (targetCount <= 0)return false;

	//至少有一个敌人在攻击范围内时，发动技能，并锁定目标
	Unit* m_parent = getParent();
	auto vec = UnitManager::getInstance()->findUnit(m_weapon->Filter);
	for (auto target : vec){
		if ((target->getPos() - m_parent->getPos()).lengthSquared() < m_weapon->Range*m_weapon->Range)
		{
			m_targetID = target->ID;
			m_targetPos = target->getPos();
			return true;
		}

	}

	return false;
}


void CSkillAttactk::onAttack(Unit* parent)
{
	Unit* m_parent = getParent();
	int targetCount = m_weapon->TargetCount;
	auto vec = UnitManager::getInstance()->findUnit(m_weapon->Filter);

	bool missTaget = true;
	for (auto target : vec){
		if (targetCount <= 0)break;

		if ((target->getPos() - parent->getPos()).lengthSquared() < m_weapon->Range*m_weapon->Range)
		{
			missTaget = false;
			m_parent->onAttack(target);
			Bullet* bullet = new Bullet(m_weapon, m_parent->ID, target->ID, parent->getPos());
			UnitManager::getInstance()->addUnit(bullet);
			targetCount--;
		}
	}

	//如果失去目标，原来锁定的目标在前摇时跑出了攻击范围，则强制攻击一开始锁定的目标
	auto target = UnitManager::getInstance()->getUnit(m_targetID);
	if (missTaget && m_weapon->TargetCount > 0 && target != nullptr)
	{
		m_parent->onAttack(target);
		Bullet* bullet = new Bullet(m_weapon, m_parent->ID, target->ID, parent->getPos());
		UnitManager::getInstance()->addUnit(bullet);
	}
}






