#include "SpellCardManager.h"


SpellCardManager* SpellCardManager::p_myinstance = nullptr;

SpellCardManager::SpellCardManager()
{

}

SpellCardManager::~SpellCardManager()
{

}

SpellCardManager* SpellCardManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new SpellCardManager();
	}
	return p_myinstance;
}

const SpellCard* SpellCardManager::getSpellCard(int id)
{
	for (auto var : m_spellTower)
	{
		if (var.second->ID == id)
			return var.second;
	}
	return nullptr;
}

const SpellCard* SpellCardManager::getSpellCard(Name name)
{
	CCASSERT(m_spellTower.find(name) != m_spellTower.end(), string("SpellCard [" + name + "] NOT found").c_str());

	if (m_spellTower.find(name) != m_spellTower.end())return m_spellTower.at(name);
	else return nullptr;
}

void SpellCardManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void SpellCardManager::LoadResource(const vector<Name>& resNameList)
{

	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/SpellCard.json");
	CCASSERT(!data.isNull(), "[SpellCard.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("SpellCard"), "illegal [SpellCard.json]");

	//3.读取json数据
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int Size = root["SpellCard"].Size();
	for (int i = 0; i < Size; i++) {
		JsonNode jNode = root["SpellCard"][i];
		string name = jNode["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			SpellCard* spellTower = new SpellCard();

			if (jNode.HasMember("ID"))				spellTower->ID = jNode["ID"].GetInt();
			if (jNode.HasMember("name"))			spellTower->name = jNode["name"].GetString();
			if (jNode.HasMember("Icon"))			spellTower->Icon = jNode["Icon"].GetInt();
			if (jNode.HasMember("behaviorName"))	spellTower->behaviorName = jNode["behaviorName"].GetString();
			if (jNode.HasMember("uiName"))			spellTower->uiName = jNode["uiName"].GetString();
			if (jNode.HasMember("uiDescription"))	spellTower->uiDescription = jNode["uiDescription"].GetString();
			if (jNode.HasMember("cost"))			spellTower->cost = jNode["cost"].GetDouble();
			if (jNode.HasMember("price"))			spellTower->price.money = jNode["price"].GetDouble();
			if (jNode.HasMember("sell"))			spellTower->sell = jNode["sell"].GetDouble();
			spellTower->costPlayer.money = spellTower->ID * 20;

			m_spellTower[name] = spellTower;
		}
	}
}

void SpellCardManager::FreeAllResource()
{

}

void SpellCardManager::FreeResource(const vector<Name>& resName)
{

}
