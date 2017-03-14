#include "TowerCardManager.h"


TowerCardManager* TowerCardManager::p_myinstance = nullptr;

TowerCardManager::TowerCardManager()
{

}

TowerCardManager::~TowerCardManager()
{

}

TowerCardManager* TowerCardManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new TowerCardManager();
	}
	return p_myinstance;
}

const TowerCard* TowerCardManager::getTowerCard(int id)
{
	for (auto var : m_card)
	{
		if (var.second->ID == id)
			return var.second;
	}
	return nullptr;
}

const TowerCard* TowerCardManager::getTowerCard(Name name)
{
	CCASSERT(m_card.find(name) != m_card.end(), string("TowerCard [" + name + "] NOT found").c_str());

	if (m_card.find(name) != m_card.end())return m_card.at(name);
	else return nullptr;
}

void TowerCardManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void TowerCardManager::LoadResource(const vector<Name>& resNameList)
{
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;

	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/TowerCard.json");
	CCASSERT(!data.isNull(), "[TowerCard.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("TowerCard") && root["TowerCard"].IsArray(), "illegal [TowerCard.json]");

	//3.读取json数据
	int Size = root["TowerCard"].Size();
	for (int i = 0; i < Size; i++) {
		JsonNode jNode = root["TowerCard"][i];
		string name = jNode["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			TowerCard* towercard = new TowerCard();

			if (jNode.HasMember("ID"))				towercard->ID = jNode["ID"].GetInt();
			if (jNode.HasMember("Icon"))			towercard->Icon = jNode["Icon"].GetString();
			if (jNode.HasMember("uiName"))			towercard->uiName = jNode["uiName"].GetString();
			if (jNode.HasMember("uiDescription"))	towercard->uiDescription = jNode["uiDescription"].GetString();
			if (jNode.HasMember("ActorName"))		towercard->ActorName = jNode["ActorName"].GetString();
			if (jNode.HasMember("HP"))				towercard->HP = jNode["HP"].GetDouble();
			if (jNode.HasMember("MP"))				towercard->MP = jNode["MP"].GetDouble();
			if (jNode.HasMember("AP"))				towercard->AP = jNode["AP"].GetDouble();
			if (jNode.HasMember("HP_RegenRate"))	towercard->HP_RegenRate = jNode["HP_RegenRate"].GetDouble();
			if (jNode.HasMember("MP_RegenRate"))	towercard->MP_RegenRate = jNode["MP_RegenRate"].GetDouble();
			if (jNode.HasMember("AP_RegenRate"))	towercard->AP_RegenRate = jNode["AP_RegenRate"].GetDouble();
			if (jNode.HasMember("Color_R"))			towercard->color.r = jNode["Color_R"].GetInt();
			if (jNode.HasMember("Color_G"))			towercard->color.g = jNode["Color_G"].GetInt();
			if (jNode.HasMember("Color_B"))			towercard->color.b = jNode["Color_B"].GetInt();
			if (jNode.HasMember("cost"))			towercard->cost = jNode["cost"].GetDouble();
			if (jNode.HasMember("price"))			towercard->price.money = jNode["price"].GetDouble();

			if (jNode.HasMember("spellPosPrice") && jNode["spellPosPrice"].IsArray())
			{
				int s = jNode["spellPosPrice"].Size();
				JsonNode node = jNode["spellPosPrice"];
				for (int i = 0; i < s; i++)
					towercard->spellPosPrice[i] = node[i].GetInt();
			}
			if (jNode.HasMember("weaponName") && jNode["weaponName"].IsArray())
			{
				int s = jNode["weaponName"].Size();
				JsonNode node = jNode["weaponName"];
				for (int i = 0; i < s; i++) 
					towercard->weaponName.push_back(node[i].GetString());
			}
			if (jNode.HasMember("skillName") && jNode["skillName"].IsArray())
			{
				int s = jNode["skillName"].Size();
				JsonNode node = jNode["skillName"];
				for (int i = 0; i < s; i++)
					towercard->skillName.push_back(node[i].GetString());
			}
			m_card[name] = towercard;
		}
	}
}

void TowerCardManager::FreeAllResource()
{
	m_card.clear();
}

void TowerCardManager::FreeResource(const vector<Name>& resName)
{
	for (auto name : resName)
	{
		auto card = m_card.at(name);
		if (card != nullptr)
		{
			m_card.erase(name);
		}
	}
}
