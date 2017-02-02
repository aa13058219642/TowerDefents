#include "BehaviorCreator.h"
#include "CBeahaviorBuff.h"
using namespace cocosgalaxy;

BehaviorCreator::BehaviorCreator()
{

}


BehaviorCreator::~BehaviorCreator()
{

}


CGameData* BehaviorCreator::Create(string className, string typeName)
{
	CGameData* data = nullptr;

	if (className == string("CBeahaviorBuff"))
	{
		data = Create(typeid(CBeahaviorBuff).hash_code(), typeName);
	}
	return data;
}

CGameData* BehaviorCreator::Create(int classHash, string typeName)
{
	CGameData* data = nullptr;

	if (classHash == typeid(CBeahaviorBuff).hash_code())
	{
		CBeahaviorBuff* beahavior = new CBeahaviorBuff();
		data = beahavior;

		rapidjson::Document jNode;
		jNode.Parse<0>(typeName.c_str());

		if (jNode.HasMember("name"))				beahavior->name = jNode["name"].GetString();
		if (jNode.HasMember("isTimeLimitBuff"))		beahavior->isTimeLimitBuff = jNode["isTimeLimitBuff"].GetBool();
		if (jNode.HasMember("lifetime"))			beahavior->m_lifetime = jNode["lifetime"].GetDouble();
		if (jNode.HasMember("cycle"))				beahavior->m_cycle = jNode["cycle"].GetDouble();
		if (jNode.HasMember("cycleCount"))			beahavior->m_cycleCount = jNode["cycleCount"].GetInt();
		if (jNode.HasMember("cycleEffect"))			beahavior->m_cycleEffect = jNode["cycleEffect"].GetString();

		if (jNode.HasMember("mod") && jNode["mod"].IsArray())
		{
			JsonNode modNode = jNode["mod"];

			int Size = modNode.Size();
			for (int i = 0; i < Size; i++) {
				CModification mod;
				if (modNode[i].HasMember("modMainType"))	mod.mainType = (EModificationMainType)modNode[i]["modMainType"].GetInt();
				if (modNode[i].HasMember("modValueType"))	mod.modType = (EModificationType)modNode[i]["modValueType"].GetInt();
				if (modNode[i].HasMember("priority"))		mod.priority = modNode[i]["priority"].GetInt();
				if (modNode[i].HasMember("valueType") && modNode[i].HasMember("value"))
				{
					JsonNode var = modNode[i]["value"];
					switch ((EModValueType)modNode[i]["valueType"].GetInt())
					{
					case EModValueType::EModValueType_int:		mod.value = Value(var.GetInt());	break;
					case EModValueType::EModValueType_float:	mod.value = Value(var.GetDouble());	break;
					case EModValueType::EModValueType_string:	mod.value = Value(var.GetString());	break;
					case EModValueType::EModValueType_bool:		mod.value = Value(var.GetBool());	break;
					default:CCASSERT(false, "Error EModValueType!"); break;
					};
				}
				beahavior->m_modList.push_back(mod);
			}
		}

	}
	
	return data;
}



