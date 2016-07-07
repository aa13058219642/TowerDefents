#include "EffectManager.h"

#include "CEffectSet.h"
#include "CEffectResponse.h"

#include "CEffectDamage.h"
#include "CEffectLaunchMissile.h"

EffectManager* EffectManager::p_myinstance = nullptr;

EffectManager::EffectManager()
{

}

EffectManager* EffectManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new EffectManager();
		p_myinstance->LoadEffectList();
	}
	return p_myinstance;
}

int EffectManager::LoadEffectList()
{
	//effectlist.insert(pair<int,string>(102,"aclive")"",(CEffect*)new CEffectDamage(100));
	effectlist["missileDamage"] = new CEffectDamage(100);
	effectlist["LaunchMissile"] = new CEffectLaunchMissile(0);



	return 0;
}

CEffect* EffectManager::createCEffect(string key, GameObject* parent, GameObject* target)
{
	if (findEffect(key)){
		CEffect* effect = effectlist[key]->clone();
		effect->setParent(parent);
		if (target == nullptr)
			effect->setTarget(parent);
		else
			effect->setTarget(target);


		return effect;
	}
	return nullptr;
}


bool EffectManager::findEffect(const string& key)
{
	return (effectlist.find(key) != effectlist.end());
}
