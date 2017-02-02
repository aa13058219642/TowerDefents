#include "EffectCreator.h"

#include "CEffectDamage.h"
#include "CEffectLaunchMissile.h"
#include "CEffectEnumArea.h"

using namespace cocosgalaxy;

EffectCreator::EffectCreator()
{

}


EffectCreator::~EffectCreator()
{

}


CGameData* EffectCreator::Create(string className, string typeName)
{
	CGameData* data = nullptr;

	if (className == string("CEffectDamage"))
	{
		data = Create(typeid(CEffectDamage).hash_code(), typeName);
	} 
	else if (className == string("CEffectEnumArea"))
	{
		data = Create(typeid(CEffectEnumArea).hash_code(), typeName);
	}
	else if (className == string("CEffectLaunchMissile"))
	{
		data = Create(typeid(CEffectLaunchMissile).hash_code(), typeName);
	}
	return data;
}

CGameData* EffectCreator::Create(int classHash, string typeName)
{
	CGameData* data = nullptr;

	if (classHash == typeid(CEffectDamage).hash_code())
	{
		CEffectDamage* effect = new CEffectDamage();
		data = effect;

		rapidjson::Document jNode;
		jNode.Parse<0>(typeName.c_str());

		if (jNode.HasMember("name"))	effect->name = jNode["name"].GetString();

		if (jNode.HasMember("param") && jNode["param"].IsObject())
		{
			JsonNode paramNode = jNode["param"];

			if (paramNode.HasMember("chance"))			effect->chance = paramNode["chance"].GetDouble();
			if (paramNode.HasMember("minDamage"))		effect->minDamage = paramNode["minDamage"].GetInt();
			if (paramNode.HasMember("maxDamage"))		effect->maxDamage = paramNode["maxDamage"].GetInt();
			if (paramNode.HasMember("damageType"))		effect->damageType = (EDamageType)paramNode["damageType"].GetInt();
			if (paramNode.HasMember("effectAnimate"))	effect->effectAnimate = paramNode["effectAnimate"].GetString();
		}
	}
	else if (classHash == typeid(CEffectEnumArea).hash_code())
	{
		CEffectEnumArea* effect = new CEffectEnumArea();
		data = effect;

		rapidjson::Document jNode;
		jNode.Parse<0>(typeName.c_str());

		if (jNode.HasMember("name"))	effect->name = jNode["name"].GetString();

		if (jNode.HasMember("param") && jNode["param"].IsObject())
		{
			JsonNode paramNode = jNode["param"];

			if (paramNode.HasMember("chance"))		effect->chance = paramNode["chance"].GetDouble();
			if (paramNode.HasMember("areaRadius"))	effect->areaRadius = paramNode["areaRadius"].GetInt();
			if (paramNode.HasMember("applyEffect"))	effect->applyEffect = paramNode["applyEffect"].GetString();
		}
	}
	else if (classHash == typeid(CEffectLaunchMissile).hash_code())
	{
		CEffectLaunchMissile* effect = new CEffectLaunchMissile();
		data = effect;

		rapidjson::Document jNode;
		jNode.Parse<0>(typeName.c_str());

		if (jNode.HasMember("name"))	effect->name = jNode["name"].GetString();

		if (jNode.HasMember("param") && jNode["param"].IsObject())
		{
			JsonNode paramNode = jNode["param"];

			if (paramNode.HasMember("chance"))			effect->chance = paramNode["chance"].GetDouble();
			if (paramNode.HasMember("className"))		effect->className = paramNode["className"].GetString();
			if (paramNode.HasMember("typeName"))		effect->typeName = paramNode["typeName"].GetString();
		}
	}
	return data;
}



