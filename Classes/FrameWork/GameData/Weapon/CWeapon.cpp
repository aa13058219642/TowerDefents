#include "CWeapon.h"
#include "CEffect.h"
using namespace cocosgalaxy;

CWeapon::CWeapon()
{
	CostBase.HP = 0;
	CostBase.MP = 0;
	CostBase.AP = 0;
	CostBase.Speed = 0;

	CostDamageRate.HP = 0;
	CostDamageRate.MP = 0;
	CostDamageRate.AP = 1.0f;
	CostDamageRate.Speed = 0;

	CostDamageRangeRate = 0.5f;


	chance = 1;
	Range = 64;

	ColdDown = 0x7fff;
	ColdDown.Max = 1;
	ColdDown.Max.ValueMin = 0.1f;
	TargetCount = 1;

	Filter = 5;
	DamageType = EDamageType::EDamageType_Weapon;

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

	//bulletType = BulletType::Ball;
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
	ColdDown.clear();
	TargetCount.clear();
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