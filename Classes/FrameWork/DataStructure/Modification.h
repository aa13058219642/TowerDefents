#pragma once
#include "stdfax.h"

enum EModificationMainType{
	EModMainType_NoType,
	EModMainType_Weapon
};

enum EModificationValueType{
	EModValueType_Weapon = 1 << 16,
	EModValueType_Weapon_MinDamage_Addend,
	EModValueType_Weapon_MinDamage_Multiplier,
	EModValueType_Weapon_MaxDamage_Addend,
	EModValueType_Weapon_MaxDamage_Multiplier,
	EModValueType_Weapon_ColdDown_Addend,
	EModValueType_Weapon_ColdDown_Multiplier,
};


class Unit;
//template<typename T>
class Modification
{
public:
	EModificationMainType mainType;
	EModificationValueType modType;
	Value value;
	int pid;
	int priority;

	Modification(EModificationMainType maintype, EModificationValueType modtype, Value value, int pid = -1, int priority = 0);
	~Modification();

	bool operator()(const Modification& mod1, const Modification& mod2);

	

	void install(Unit* unit, bool isUninstall = false);
	void uninstall(Unit* unit);

private:

	void setModification(Unit* unit, Value value);




};