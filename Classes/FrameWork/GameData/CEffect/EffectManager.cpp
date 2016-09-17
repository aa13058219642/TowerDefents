#include "EffectManager.h"

#include "CEffectSet.h"
#include "CEffectResponse.h"

#include "CEffectDamage.h"
#include "CEffectLaunchMissile.h"
#include "CEffectEnumArea.h"

EffectManager* EffectManager::p_myinstance = nullptr;

EffectManager::EffectManager()
{

}

EffectManager* EffectManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new EffectManager();
	}
	return p_myinstance;
}

void EffectManager::LoadResource(const vector<Name>& resNameList)
{
	m_effectlist["missileDamage"] = new CEffectDamage(2,4);
	m_effectlist["missileDamageBoom"] = new CEffectDamage(100, 200, EDamageType_Real, "e002");
	m_effectlist["MissileBoom"] = new CEffectEnumArea(EUnitType::Unit_Monster, 300,"missileDamageBoom");
	m_effectlist["LaunchBall"] = new CEffectLaunchMissile(0);
	m_effectlist["LaunchMissile"] = new CEffectLaunchMissile(1);
	m_effectlist["LaunchBoom"] = new CEffectLaunchMissile(2);

}

void EffectManager::FreeAllResource()
{
	for (auto var : m_effectlist)
		delete var.second;
	m_effectlist.clear();
}

void EffectManager::FreeResource(const vector<Name>& resName)
{
	for (auto name : resName)
	{
		if (m_effectlist.find(name) != m_effectlist.end())
		{
			delete m_effectlist[name];
			m_effectlist.erase(name);
		}
	}
}

CEffect* EffectManager::createCEffect(string key, int parentID, int targetID)
{
	if (findEffect(key)){
		CEffect* effect = m_effectlist[key]->clone();
		effect->setParent(parentID);
		if (targetID == -1)
			effect->setTarget(parentID);
		else
			effect->setTarget(targetID);
		return effect;
	}
	log("EffectManager->createCEffect() : CEffect [%s] Not Found !", key.c_str());
	return nullptr;
}

CEffect* EffectManager::createHitEffect(CWeapon* weapon, int parentID, int targetID)
{
	CEffectSet* effect = new CEffectSet();

	//¼ÆËã±©»÷¼Ó³É
	bool isCritical = false;
	float mul = 1;
	if (rand_0_1() < weapon->criticalChance)
	{
		mul = weapon->criticalMultiplier;
		isCritical = true;
	}

	//ÊÇ·ñ·¶Î§¹¥»÷
	if (weapon->BoomRange == 0)
	{
		//effect->addEffect(new CEffectDamage(weapon->MinDamage*mul, weapon->MaxDamage*mul, weapon->DamageType, weapon->attack_Animate, parentID, targetID));
		effect->addEffect(new CEffectDamage(weapon->Damage.Min, weapon->Damage.Max*mul, weapon->DamageType, weapon->attack_Animate, parentID, targetID));
		if (!string(weapon->attack_Effect).empty())
			effect->addEffect(createCEffect(weapon->attack_Effect, parentID, targetID));
		if (isCritical && !string(weapon->critical_Effect).empty())
			effect->addEffect(createCEffect(weapon->critical_Effect, parentID, targetID));

	}
	else
	{
		CEffectSet* set = new CEffectSet();
		//set->addEffect(new CEffectDamage(weapon->MinDamage*mul, weapon->MaxDamage*mul, weapon->DamageType, weapon->attack_Animate, parentID, targetID));
		set->addEffect(new CEffectDamage(weapon->Damage.Min, weapon->Damage.Max*mul, weapon->DamageType, weapon->attack_Animate, parentID, targetID));
		
		if (!string(weapon->attack_Effect).empty())
			set->addEffect(createCEffect(weapon->attack_Effect, parentID, targetID));
		if (isCritical && !string(weapon->critical_Effect).empty())
			set->addEffect(createCEffect(weapon->critical_Effect, parentID, targetID));
		effect->addEffect(new CEffectEnumArea(weapon->Filter, weapon->BoomRange, "", set, parentID));
	}
	return effect;
}

bool EffectManager::findEffect(const string& key)
{
	return (m_effectlist.find(key) != m_effectlist.end());
}
