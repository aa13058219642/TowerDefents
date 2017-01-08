#pragma once

//
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

//USING_NS_CC;
////using namespace cocos2d::ui;
////using namespace cocostudio;

//Cocos Galaxy
namespace cocosgalaxy
{
	using namespace cocos2d;
	using std::string;
	using std::vector;
	using std::map;
	using std::list;

	typedef std::string Name;



	/////////////////////////////////////////////////////////////////////////////
	//CUnit/////////////////////////////////////////////////////////////////

	typedef unsigned int UnitType;
	namespace EUnitType
	{
		const UnitType Unit = 1;
		const UnitType Land = 1 << 2;
		const UnitType Fly = 1 << 3;
		const UnitType Death = 1 << 29;
		const UnitType Destory = 1 << 30;
	};

	//enum EUnitType : unsigned int
	//{
	//	Unit_Unit = 1,
	//	Unit_Tower = 1 << 1,
	//	Unit_Monster = 1 << 2,
	//	Unit_Bullet = 1 << 3,
	//	Unit_Land = 1 << 4,
	//	Unit_Fly = 1 << 5,
	//	Unit_Death = 1 << 29,
	//	Unit_Destory = 1 << 30
	//};

	enum EUnitState{
		UnitState_Normal,
		UnitState_UsingSkill,
		UnitState_Death,
		UnitState_Destory
	};




	/////////////////////////////////////////////////////////////////////////////
	//CEffect/////////////////////////////////////////////////////////////////
#define DamageTypeCount 3
	enum EDamageType : unsigned int{
		EDamageType_Weapon,
		EDamageType_Magic,
		EDamageType_Real
	};

	/////////////////////////////////////////////////////////////////////////////
	//CSkill/////////////////////////////////////////////////////////////////


	enum ESkillType
	{
		ECSkill,
		ECSkillAttack,
		ECSkillEffect,
		ECSkillEffectInstant
	};


	enum ESkillEffectState
	{
		SkillEffectState_ColdDowning,
		SkillEffectState_Ready,
		SkillEffectState_Approaching,
		SkillEffectState_Preparing,
		SkillEffectState_Beforing,
		SkillEffectState_Using,
		SkillEffectState_Aftering,
		SkillEffectState_End
	};

	/////////////////////////////////////////////////////////////////////////////
	//CWeapon///////////////////////////////////////////////////////////////////////////
	enum EWeapon_Upgradable
	{
		WeaponUpgradable_Range,
		WeaponUpgradable_ColdDown,
		WeaponUpgradable_TargetCount,
		WeaponUpgradable_Filter,
		WeaponUpgradable_Damage,
		WeaponUpgradable_MinDamage,
		WeaponUpgradable_MaxDamage,
		WeaponUpgradable_DamageType
	};


	/////////////////////////////////////////////////////////////////////////////
}









