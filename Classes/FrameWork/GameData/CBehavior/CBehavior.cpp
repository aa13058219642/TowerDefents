#include "CBehavior.h"
using namespace cocosgalaxy;

CBehavior::CBehavior()
{
	//m_type = EBehaviorType::ECBehavior;
	m_state = EBehaviorState::EBehaviorState_Unused;
	m_parent = nullptr;
}


CBehavior::~CBehavior()
{

}

//void CBehavior::setParent(CUnit* parent)
//{
//	this->m_patert = parent;
//}


//EBehaviorType CBehavior::getType()
//{
//	return m_type;
//}



bool CBehavior::isDeath()
{
	return m_state == EBehaviorState::EBehaviorState_Death;
}
