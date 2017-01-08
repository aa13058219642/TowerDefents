#include "WeaponManager.h"

WeaponManager* WeaponManager::p_myinstance = nullptr;

WeaponManager::WeaponManager(){}

WeaponManager::~WeaponManager()
{
}


WeaponManager* WeaponManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new WeaponManager();
	}
	return p_myinstance;
}

void WeaponManager::LoadResource()
{
	this->LoadResource(vector<Name>());
}

void WeaponManager::LoadResource(const vector<Name> & resNameList)
{
	//1.打开文件
	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/Weapon.json");
	CCASSERT(!data.isNull(), "[Weapon.json] NOT found");

	//2.载入json
	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("Weapon") && root["Weapon"].IsArray(), "illegal [Weapon.json]: weapondata error");

	//3.读取json数据
	//CCASSERT(root["weapondata"].HasMember("count"), "illegal [Weapon.json]: weapondata.count NOT found");
	//int count = root["weapondata"]["count"].GetInt();
	float scale =1 / Director::getInstance()->getContentScaleFactor();

	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int Size = root["Weapon"].Size();
	for (int i = 0; i < Size; i++) {
		//string index = StringUtils::format("w%03d",i);
		//CCASSERT(root["weapondata"].HasMember(index.c_str()) && root["weapondata"][index.c_str()].IsObject(), string("illegal [Weapon.json]: weapondata" + index + " NOT found").c_str());

		JsonNode jNode = root["Weapon"][i];
		string name = jNode["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			CWeapon* weapon = new CWeapon();

			if (jNode.HasMember("chance"))				weapon->chance				= jNode["chance"].GetDouble();
			if (jNode.HasMember("Range"))				weapon->Range				= jNode["Range"].GetDouble() * scale;
			if (jNode.HasMember("ColdDown"))			weapon->ColdDown.Max		= jNode["ColdDown"].GetDouble();
			if (jNode.HasMember("TargetCount"))			weapon->TargetCount			= jNode["TargetCount"].GetInt();
			if (jNode.HasMember("Filter"))				weapon->Filter				= jNode["Filter"].GetUint();
			if (jNode.HasMember("DamageType"))			weapon->DamageType			= (EDamageType)jNode["DamageType"].GetInt();
			if (jNode.HasMember("MinDamage"))			weapon->Damage.Min			= jNode["MinDamage"].GetDouble();
			if (jNode.HasMember("MaxDamage"))			weapon->Damage.Max			= jNode["MaxDamage"].GetDouble();
			if (jNode.HasMember("BoomRange"))			weapon->BoomRange			= jNode["BoomRange"].GetDouble() * scale;
			if (jNode.HasMember("attack_Effect"))		weapon->attack_Effect		= jNode["attack_Effect"].GetString();
			if (jNode.HasMember("attack_Animate"))		weapon->attack_Animate		= jNode["attack_Animate"].GetString();
			if (jNode.HasMember("criticalChance"))		weapon->criticalChance		= jNode["criticalChance"].GetDouble();
			if (jNode.HasMember("criticalMultiplier"))	weapon->criticalMultiplier	= jNode["criticalMultiplier"].GetDouble();
			if (jNode.HasMember("critical_Effect"))		weapon->critical_Effect		= jNode["critical_Effect"].GetString();
			if (jNode.HasMember("critical_Animate"))	weapon->critical_Animate	= jNode["critical_Animate"].GetString();
			if (jNode.HasMember("ActorName"))			weapon->ActorName			= jNode["ActorName"].GetString();
			if (jNode.HasMember("beforing_Delay"))		weapon->beforing_Delay		= jNode["beforing_Delay"].GetDouble();
			if (jNode.HasMember("using_Delay"))			weapon->using_Delay			= jNode["using_Delay"].GetDouble();
			if (jNode.HasMember("aftering_Delay"))		weapon->aftering_Delay		= jNode["aftering_Delay"].GetDouble();
			if (jNode.HasMember("beforing_Animate"))	weapon->beforing_Animate	= jNode["beforing_Animate"].GetString();
			if (jNode.HasMember("using_Animate"))		weapon->using_Animate		= jNode["using_Animate"].GetString();
			if (jNode.HasMember("aftering_Animate"))	weapon->aftering_Animate	= jNode["aftering_Animate"].GetString();
			//if (jNode.HasMember("bulletType"))			weapon->bulletType			= (BulletType)jNode["bulletType"].GetInt();
			if (jNode.HasMember("IsTrackTarget"))		weapon->IsTrackTarget		= jNode["IsTrackTarget"].GetBool();
			if (jNode.HasMember("IsFaceToTarget"))		weapon->IsFaceToTarget		= jNode["IsFaceToTarget"].GetBool();
			if (jNode.HasMember("BulletSpeed"))			weapon->BulletSpeed			= jNode["BulletSpeed"].GetDouble();

			m_weapon[name] = weapon;
		}
	}
	
}

void WeaponManager::FreeAllResource()
{
	for (auto var : m_weapon)
		delete var.second;
	m_weapon.clear();

}

void WeaponManager::FreeResource(const vector<Name>& resName)
{
	for (auto name : resName)
	{
		if (m_weapon.find(name) != m_weapon.end())
		{
			delete m_weapon[name];
			m_weapon.erase(name);
		}
	}
}

CWeapon* WeaponManager::getWeapon(const string& weaponName)
{
	CCASSERT(m_weapon.find(weaponName) != m_weapon.end(), string("Weapon [" + weaponName + "] NOT found").c_str());

	if (m_weapon.find(weaponName) != m_weapon.end())return new CWeapon(*m_weapon[weaponName]);
	else return nullptr;
}





