#include "BulletManager.h"


BulletManager* BulletManager::p_myinstance = nullptr;

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{

}

BulletManager* BulletManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new BulletManager();
	}
	return p_myinstance;
}



void BulletManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void BulletManager::LoadResource(const vector<Name>& resNameList)
{
	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Bullet.json");
	CCASSERT(!data.isNull(), "[Bullet.json] Lost!");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("bullet"), "illegal [Bullet.json]");

	//3.读取json数据
	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int size = root["bullet"].Size();
	for (int i = 0; i < size; i++) {
		JsonNode jnode = root["bullet"][i];

		Bullet* bullet = new Bullet();
		if (jnode.HasMember("name"))				bullet->name = jnode["name"].GetString();
		if (jnode.HasMember("type"))				bullet->setType((UnitType)jnode["type"].GetUint());
		if (jnode.HasMember("Radius"))				bullet->Radius = jnode["Radius"].GetInt();
		if (jnode.HasMember("Speed"))				bullet->Speed = jnode["Speed"].GetInt();
		if (jnode.HasMember("HitEffect"))			bullet->setOnHitEffect(EffectManager::getInstance()->createCEffect(string(jnode["HitEffect"].GetString())));
		if (jnode.HasMember("ActorName"))			bullet->setActorName(string(jnode["ActorName"].GetString()));

		bulletlist[bullet->name] = bullet;
	}
}

void BulletManager::FreeAllResource()
{

}

void BulletManager::FreeResource(const vector<Name>& resName)
{

}

Bullet* BulletManager::CreateBullet(string bulletName)
{
	Bullet* bullet = nullptr;
	for (auto& b : bulletlist)
	{
		if (b.second->name == bulletName)
		{
			bullet = b.second->clone();
		}
	}
	CCASSERT(bullet != nullptr, string("Unknow bullet name [" + bulletName + "]!").c_str());
	return bullet;
}












