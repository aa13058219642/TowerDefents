#include "EffectManager.h"
#include "CEffectSet.h"
#include "CEffectResponse.h"

#include "CEffectDamage.h"
#include "CEffectLaunchMissile.h"
#include "CEffectEnumArea.h"
using namespace cocosgalaxy;

EffectManager* EffectManager::p_myinstance = nullptr;

EffectManager::EffectManager()
{
	isInit = false;
	effectCreator = nullptr;
}

EffectManager* EffectManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new EffectManager();
	}
	return p_myinstance;
}

void EffectManager::init(EffectCreator* effectCreator)
{
	if (effectCreator == nullptr)
	{
		this->effectCreator = new EffectCreator();
	}
	else
	{
		this->effectCreator = effectCreator;
	}
	isInit = true;
}



void EffectManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void EffectManager::LoadResource(const vector<Name>& resNameList)
{
	CCASSERT(isInit, "the EffectManager is NOT init !");

	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Effect.json");
	CCASSERT(!data.isNull(), "[Effect.json] NOT found");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("Effects") && root["Effects"].IsArray(), "illegal [Effect.json]: EffectsData error");

	//3.读取json数据
	float scale = 1 / Director::getInstance()->getContentScaleFactor();

	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int Size = root["Effects"].Size();
	for (int i = 0; i < Size; i++) {
		JsonNode jNode = root["Effects"][i];
		string name = jNode["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			string className = jNode["class"].GetString();
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			jNode.Accept(writer);
			m_effectlist[name] = static_cast<CEffect*>(effectCreator->Create(className, buffer.GetString()));
		}
	}
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
	CCASSERT(false, StringUtils::format("EffectManager->createCEffect() : CEffect [%s] Not Found !", key.c_str()).c_str());
	return nullptr;
}

CEffect* EffectManager::createHitEffect(CWeapon* weapon, int parentID, int targetID)
{
	CEffectSet* effect = new CEffectSet();

	//计算暴击加成
	bool isCritical = false;
	float mul = 1;
	if (rand_0_1() < weapon->criticalChance)
	{
		mul = weapon->criticalMultiplier;
		isCritical = true;
	}

	//是否范围攻击
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
