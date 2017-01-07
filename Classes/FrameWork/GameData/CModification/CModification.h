#pragma once
#include "GalaxyBase.h"
#include "CUnit.h"

namespace cocosgalaxy{
	
	enum EModificationMainType{
		EModMainType_NoType,
		EModMainType_Weapon
	};

	enum EModificationType{
		EModType_None,

		EModType_Weapon = 1 << 16,
		EModType_Weapon_Chance_Addend,
		EModType_Weapon_Chance_Multiplier,
		EModType_Weapon_ColdDown_Addend,
		EModType_Weapon_ColdDown_Multiplier,
		EModType_Weapon_Range_Addend,
		EModType_Weapon_Range_Multiplier,
		EModType_Weapon_TargetCount_Addend,
		EModType_Weapon_TargetCount_Multiplier,
		EModType_Weapon_MinDamage_Addend,
		EModType_Weapon_MinDamage_Multiplier,
		EModType_Weapon_MaxDamage_Addend,
		EModType_Weapon_MaxDamage_Multiplier,
		EModType_Weapon_BoomRange_Addend,
		EModType_Weapon_BoomRange_Multiplier,
		EModType_Weapon_CriticalChance_Addend,
		EModType_Weapon_CriticalChance_Multiplier,
		EModType_Weapon_CriticalMultiplier_Addend,
		EModType_Weapon_CriticalMultiplier_Multiplier,

		EModType_Weapon_DamageType_Addend,
		EModType_Weapon_AttackEffect_Addend,
		EModType_Weapon_AttackAnimate_Addend,
		EModType_Weapon_CriticalEffect_Addend,
		EModType_Weapon_CriticslAnimate_Addend,
		EModType_Weapon_ActorName_Addend,
	};

	enum EModValueType{
		EModValueType_int,
		EModValueType_float,
		EModValueType_string,
		EModValueType_bool
	};

	 
	class CModification
	{
	public:
		EModificationMainType mainType;
		EModificationType modType;
		Value value;
		int pid;
		int priority;

		CModification();
		CModification(EModificationMainType maintype, EModificationType modtype, Value value, int priority = 0, int pid = -1);
		~CModification();

		bool operator()(const CModification& mod1, const CModification& mod2);

		void install(CUnit* unit, bool isUninstall = false);
		void uninstall(CUnit* unit);

	private:
		void setModification(CUnit* unit, Value value);

	};


}