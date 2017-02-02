#include "CSkill.h"
#include "UnitManager.h"
using namespace cocosgalaxy;

CSkill::CSkill()
{
	ID = 0;
	name = "";
	groupID = "";
	m_type = ESkillType::ECSkill;
	m_parentID = -1;
	m_targetID = -1;
	m_targetPos = Point::ZERO;
}


CSkill::~CSkill()
{

}


void CSkill::setType(ESkillType type)
{
	m_type = type;
}
ESkillType CSkill::getType()
{
	return m_type;
}

void CSkill::setParent(int parentID)
{
	m_parentID = parentID;
}

CUnit* CSkill::getParent()
{
	return UnitManager::getInstance()->getUnit(m_parentID);
}


