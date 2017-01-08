#include "SkillManager.h"
#include "CSkillEffectInstant.h"
#include "CSkillAttactk.h"

using namespace cocosgalaxy;

SkillManager* SkillManager::p_myinstance = NULL;

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

SkillManager* SkillManager::getInstance()
{
	if (p_myinstance == NULL)
	{
		p_myinstance = new SkillManager();
	}
	return p_myinstance;
}

void SkillManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void SkillManager::LoadResource(const vector<Name>& resNameList)
{
	//Skill Nuke
	CSkillEffectInstant* skilleffect = new CSkillEffectInstant();
	skilleffect->Fliter = 5;
	skilleffect->Range = 300;
	skilleffect->AutoUseRange = 300;
	skilleffect->preparing_Delay = 0.4f;
	skilleffect->preparing_Animate = "skill_preparing";
	skilleffect->beforing_Delay = 1.0f;
	skilleffect->beforing_Animate = "skill_beforing";
	skilleffect->using_Delay = 0.5f;
	skilleffect->using_Animate = "skill_using";
	skilleffect->aftering_Delay = 0.2f;
	skilleffect->aftering_Effect = "LaunchMissile";
	skilleffect->aftering_Animate = "skill_aftering";
	skilleffect->ColdDown = 3;
	skilleffect->ColdDowning = 3;
	skilleffect->name = "Nuke";
	m_skilllist["Nuke"] = skilleffect;

	CSkillAttactk* skillattack = new CSkillAttactk();
	m_skilllist["attack"] = skillattack;

}

void SkillManager::FreeAllResource()
{
	for (auto var : m_skilllist)
		delete var.second;
	m_skilllist.clear();
}

void SkillManager::FreeResource(const vector<Name>& resName)
{
	for (auto name : resName)
	{
		if (m_skilllist.find(name) != m_skilllist.end())
		{
			delete m_skilllist[name];
			m_skilllist.erase(name);
		}
	}
}

CSkill* SkillManager::createCSkill(string key, CUnit* parent)
{
	if (findSkill(key)){
		CSkill* skill = m_skilllist[key]->clone();
		skill->setParent(parent->ID);
		return skill;
	}
	CCASSERT(false, StringUtils::format("SkillManager->createCSkill() : CSkill [%s] Not Found !", key.c_str()).c_str());

	return nullptr;
}

bool SkillManager::findSkill(const string& key)
{
	return (m_skilllist.find(key) != m_skilllist.end());
}







