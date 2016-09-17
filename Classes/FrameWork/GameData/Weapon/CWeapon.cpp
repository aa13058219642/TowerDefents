#include "CWeapon.h"
#include "CEffect.h"

CWeapon::CWeapon()
{
	chance = 1;
	Range = 64;
	CoolDown = 1;
	TargetCount = 1;
	Filter = EUnitType::Unit_Monster;
	DamageType = EDamageType::EDamageType_Weapon;
	//MinDamage = 1;
	//MaxDamage = 1;

	Damage.Min = 1;
	Damage.Max = 1;

	BoomRange = 0;
	attack_Effect = "";
	attack_Animate = "";
	criticalChance = 0.05f;
	criticalMultiplier = 2;
	critical_Effect = "";
	critical_Animate = "";

	ActorName = "";
	beforing_Delay = 0;
	using_Delay = 0;
	aftering_Delay = 0;
	beforing_Animate = "";
	using_Animate = "";
	aftering_Animate = "";

	bulletType = BulletType::Ball;
	IsTrackTarget = true;
	IsFaceToTarget = false;
	BulletSpeed = 800;
}


CWeapon::~CWeapon()
{

}

CWeapon* CWeapon::clone()
{
	return new CWeapon(*this);
}


void CWeapon::clearAbility()
{
	chance.clear();
	Range.clear();
	CoolDown.clear();
	TargetCount.clear();
	//MinDamage.clear();
	//MaxDamage.clear();
	BoomRange.clear();
	criticalChance.clear();
	criticalMultiplier.clear();
	chance.clear();

	Damage.clear();
}





//
//
//template <typename T>
//void CWeapon::Upgrade(EWeapon_Upgradable type, T value)
//{
//
//
//
//
//}
//
//
//void CWeapon::Downgrade()
//{
//
//}