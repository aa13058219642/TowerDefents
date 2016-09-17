#include "CSkill.h"
#include "UnitManager.h"

CSkill::CSkill()
{
	ID = 0;
	name = "";
	groupID = "";
	m_type = ESkillType::ECSkill;
	m_parentID = -1;
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
Unit* CSkill::getParent()
{
	return UnitManager::getInstance()->getUnit(m_parentID);
}


