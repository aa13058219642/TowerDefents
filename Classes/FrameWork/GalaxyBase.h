#pragma once

//
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "json\stringbuffer.h"
#include "json\writer.h"
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
	typedef rapidjson::GenericValue<rapidjson::UTF8<char>>& JsonNode;



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









