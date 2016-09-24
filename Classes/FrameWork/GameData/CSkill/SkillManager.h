#pragma once
#include "stdfax.h"
#include "CSkill.h"
#include "ResourceLoader.h"

class SkillManager :public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static SkillManager* getInstance();
	~SkillManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	CSkill* createCSkill(string key, Unit* parent);
	bool findSkill(const string& key);


private:
	SkillManager();
	static SkillManager* p_myinstance;


	std::map<string, CSkill*> m_skilllist;
};



