#include "BehaviorManager.h"

#include "CBeahaviorBuff.h"


BehaviorManager* BehaviorManager::p_myinstance = nullptr;

BehaviorManager::BehaviorManager()
{

}

BehaviorManager::~BehaviorManager()
{

}

BehaviorManager* BehaviorManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new BehaviorManager();
	}
	return p_myinstance;
}

void BehaviorManager::LoadResource(const vector<Name>& resNameList)
{
	CBeahaviorBuff* buf = new CBeahaviorBuff();
	buf->m_modList.push_back(
		Modification(
		EModificationMainType::EModMainType_Weapon,
		EModificationValueType::EModValueType_Weapon_MaxDamage_Multiplier,
		Value(10), -1, 10));
	m_behaviorList["buuf1"]=buf;
}

void BehaviorManager::FreeAllResource()
{
	for (auto var : m_behaviorList)
		delete var.second;
	m_behaviorList.clear();
}

void BehaviorManager::FreeResource(const vector<Name>& resName)
{

}


CBehavior* BehaviorManager::createBehavior(string key, int parentID, int targetID)
{
	if (m_behaviorList.find(key) != m_behaviorList.end()){
		CBehavior* behavior = m_behaviorList[key]->clone();
		return behavior;
	}
	log("EffectManager->createCEffect() : CEffect [%s] Not Found !", key.c_str());
	return nullptr;
}





