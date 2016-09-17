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
	CCASSERT(root.IsObject() && root.HasMember("weapondata"), "illegal [Weapon.json]: weapondata error");

	//3.读取json数据
	CCASSERT(root["weapondata"].HasMember("count"), "illegal [Weapon.json]: weapondata.count NOT found");
	int count = root["weapondata"]["count"].GetInt();
	float scale = Director::getInstance()->getContentScaleFactor();

	for (int i = 1; i <= count; i++) {
		string index = StringUtils::format("w%03d",i);
		CCASSERT(root["weapondata"].HasMember(index.c_str()) && root["weapondata"][index.c_str()].IsObject(), string("illegal [Weapon.json]: weapondata" + index + " NOT found").c_str());

		auto& jNote = root["weapondata"][index.c_str()];
		string name = jNote["name"].GetString();
		if (std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			CWeapon* weapon = new CWeapon();

			if (jNote.HasMember("chance"))				weapon->chance				= jNote["chance"].GetDouble();
			if (jNote.HasMember("Range"))				weapon->Range				= jNote["Range"].GetDouble() / scale;
			if (jNote.HasMember("CoolDown"))			weapon->CoolDown			= jNote["CoolDown"].GetDouble();
			if (jNote.HasMember("TargetCount"))			weapon->TargetCount			= jNote["TargetCount"].GetInt();
			if (jNote.HasMember("Filter"))				weapon->Filter				= jNote["Filter"].GetUint();
			if (jNote.HasMember("DamageType"))			weapon->DamageType			= (EDamageType)jNote["DamageType"].GetInt();
			if (jNote.HasMember("MinDamage"))			weapon->Damage.Min			= jNote["MinDamage"].GetDouble();
			if (jNote.HasMember("MaxDamage"))			weapon->Damage.Max			= jNote["MaxDamage"].GetDouble();
			if (jNote.HasMember("BoomRange"))			weapon->BoomRange			= jNote["BoomRange"].GetDouble() / scale;
			if (jNote.HasMember("attack_Effect"))		weapon->attack_Effect		= jNote["attack_Effect"].GetString();
			if (jNote.HasMember("attack_Animate"))		weapon->attack_Animate		= jNote["attack_Animate"].GetString();
			if (jNote.HasMember("criticalChance"))		weapon->criticalChance		= jNote["criticalChance"].GetDouble();
			if (jNote.HasMember("criticalMultiplier"))	weapon->criticalMultiplier	= jNote["criticalMultiplier"].GetDouble();
			if (jNote.HasMember("critical_Effect"))		weapon->critical_Effect		= jNote["critical_Effect"].GetString();
			if (jNote.HasMember("critical_Animate"))	weapon->critical_Animate	= jNote["critical_Animate"].GetString();
			if (jNote.HasMember("ActorName"))			weapon->ActorName			= jNote["ActorName"].GetString();
			if (jNote.HasMember("beforing_Delay"))		weapon->beforing_Delay		= jNote["beforing_Delay"].GetDouble();
			if (jNote.HasMember("using_Delay"))			weapon->using_Delay			= jNote["using_Delay"].GetDouble();
			if (jNote.HasMember("aftering_Delay"))		weapon->aftering_Delay		= jNote["aftering_Delay"].GetDouble();
			if (jNote.HasMember("beforing_Animate"))	weapon->beforing_Animate	= jNote["beforing_Animate"].GetString();
			if (jNote.HasMember("using_Animate"))		weapon->using_Animate		= jNote["using_Animate"].GetString();
			if (jNote.HasMember("aftering_Animate"))	weapon->aftering_Animate	= jNote["aftering_Animate"].GetString();
			if (jNote.HasMember("bulletType"))			weapon->bulletType			= (BulletType)jNote["bulletType"].GetInt();
			if (jNote.HasMember("IsTrackTarget"))		weapon->IsTrackTarget		= jNote["IsTrackTarget"].GetBool();
			if (jNote.HasMember("IsFaceToTarget"))		weapon->IsFaceToTarget		= jNote["IsFaceToTarget"].GetBool();
			if (jNote.HasMember("BulletSpeed"))			weapon->BulletSpeed			= jNote["BulletSpeed"].GetDouble();

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
	return new CWeapon(*m_weapon[weaponName]);
}





