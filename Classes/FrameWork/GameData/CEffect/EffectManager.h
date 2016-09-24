#pragma once
#include "CEffect.h"
#include "CWeapon.h"
#include "ResourceLoader.h"


class EffectManager :public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static EffectManager* getInstance();
	~EffectManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	CEffect* createCEffect(string key, int parentID = -1, int targetID = -1);
	CEffect* createHitEffect(CWeapon* weapon, int parentID, int targetID);

	bool findEffect(const string& key);
private:
	static EffectManager* p_myinstance;
	std::map<string, CEffect*> m_effectlist;

	EffectManager();
};



