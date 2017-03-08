#include "MonsterManager.h"


MonsterManager* MonsterManager::p_myinstance = nullptr;

MonsterManager::MonsterManager()
{

}

MonsterManager::~MonsterManager()
{

}

MonsterManager* MonsterManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new MonsterManager();
	}
	return p_myinstance;
}



void MonsterManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void MonsterManager::LoadResource(const vector<Name>& resNameList)
{
	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Monsters.json");
	CCASSERT(!data.isNull(), "[Monsters.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("Monsters"), "illegal [Monsters.json]");

	//3.读取json数据
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int size = root["Monsters"].Size();
	for (int i = 0; i < size; i++) {
		JsonNode jnode = root["Monsters"][i];

		Monster* monster = new Monster();
		if (jnode.HasMember("id"))				monster->ID = jnode["id"].GetInt();
		if (jnode.HasMember("name"))			monster->name = jnode["name"].GetString();
		if (jnode.HasMember("Icon"))			monster->icon = jnode["Icon"].GetString();
		if (jnode.HasMember("ActorName"))		monster->setActorName(string(jnode["ActorName"].GetString()));
		if (jnode.HasMember("HP"))				monster->HP = AbilityEx<float>(jnode["HP"].GetInt(), 0, jnode["HP"].GetInt());
		if (jnode.HasMember("MP"))				monster->MP = AbilityEx<float>(jnode["MP"].GetInt(), 0, jnode["MP"].GetInt());
		if (jnode.HasMember("AP"))				monster->AP = AbilityEx<float>(jnode["AP"].GetInt(), 0, jnode["AP"].GetInt());
		if (jnode.HasMember("HP_RegenRate"))	monster->HP_RegenRate = jnode["HP_RegenRate"].GetInt();
		if (jnode.HasMember("price"))			monster->price = jnode["price"].GetInt();
		if (jnode.HasMember("Speed"))			monster->Speed = jnode["Speed"].GetInt();
		if (jnode.HasMember("unitType"))		monster->setType(jnode["unitType"].GetUint());

		//if (jnode.HasMember("skillName") && jnode["skillName"].IsArray())
		//{
		//	int s = jnode["skillName"].Size();
		//	JsonNode node = jnode["skillName"];
		//	for (int i = 0; i < s; i++)
		//		monster->skillName.push_back(node[i].GetString());
		//}

		monsterslist[monster->name] = monster;
	}
}

void MonsterManager::FreeAllResource()
{

}

void MonsterManager::FreeResource(const vector<Name>& resName)
{

}

Monster* MonsterManager::CreateMonster(string monsterName)
{
	Monster* monster = nullptr;
	for (auto& m : monsterslist)
	{
		if (m.second->name == monsterName)
		{
			monster = m.second->clone();
		}
	}
	CCASSERT(monster != nullptr, string("Unknow monster name [" + monsterName + "]!").c_str());
	return monster;
}

Monster* MonsterManager::CreateMonster(int monsterID)
{
	Monster* monster = nullptr;
	for (auto& m : monsterslist)
	{
		if (m.second->ID == monsterID)
		{
			monster = m.second->clone();
		}
	}
	CCASSERT(monster != nullptr, StringUtils::format("Unknow monster ID [%d]!", monsterID).c_str());
	return monster;
}










