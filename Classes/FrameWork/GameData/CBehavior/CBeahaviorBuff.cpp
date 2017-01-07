#include "CBeahaviorBuff.h"
using namespace cocosgalaxy;

CBeahaviorBuff::CBeahaviorBuff()
{
	m_type = EBehaviorType::ECBeahaviorBuff;
	isTimeLimitBuff = false;
	m_lifetime = 0;
	m_cycle = 0;
	m_cycleCount = -1;
	m_cycleEffect = "";
}


CBeahaviorBuff::~CBeahaviorBuff()
{

}

CBehavior* CBeahaviorBuff::clone()
{
	CBeahaviorBuff* behavior = new CBeahaviorBuff();

	behavior->m_type = this->m_type;
	behavior->cost = this->cost;
	behavior->m_modList = this->m_modList;
	behavior->m_lifetime = this->m_lifetime;


	return behavior;
}


bool CBeahaviorBuff::meetRequirement()
{
	return true;
}

void CBeahaviorBuff::update(float dt)
{
	if (isTimeLimitBuff)
	{
		m_lifetime -= dt;
		if (m_lifetime <= 0)
		{
			this->Uninstall(m_parent);
		}
	}
}


void CBeahaviorBuff::Install(CUnit* parent)
{
	m_parent = parent;

	for (auto& var : m_modList)
	{
		var.install(m_parent);
	}
	m_state = EBehaviorState::EBehaviorState_Using;
}

void CBeahaviorBuff::Uninstall(CUnit* parent)
{
	m_parent = parent;
	for (auto& var : m_modList)
	{
		var.uninstall(m_parent);
	}
	m_state = EBehaviorState::EBehaviorState_Death;
}









