#include "Modification.h"
#include "Unit.h"

//Modification::Modification()
//{
//
//}


Modification::~Modification()
{

}

Modification::Modification(EModificationMainType maintype, EModificationValueType modtype, Value value, int pid, int priority)
{
	this->mainType = maintype;
	this->modType = modtype;
	this->value = value;
	this->pid = pid;
	this->priority = priority;
}

bool Modification::operator()(const Modification& mod1, const Modification& mod2)
{
	return mod1.priority < mod2.priority;
}



void Modification::install(Unit* unit, bool isUninstall)
{
	switch (mainType)
	{
	case EModificationMainType::EModMainType_NoType:

		break;
	case EModificationMainType::EModMainType_Weapon:
		switch (modType)
		{
		case EModValueType_Weapon:
			break;
		case EModValueType_Weapon_MinDamage_Addend:
			unit->getWeapon()->Damage.Min.add(this->value.asFloat(), isUninstall);
			break;
		case EModValueType_Weapon_MinDamage_Multiplier:
			unit->getWeapon()->Damage.Min.mul(this->value.asFloat(), isUninstall);
			break;
		case EModValueType_Weapon_MaxDamage_Addend:
			unit->getWeapon()->Damage.Max.add(this->value.asFloat(), isUninstall);
			break;
		case EModValueType_Weapon_MaxDamage_Multiplier:
			unit->getWeapon()->Damage.Max.mul(this->value.asFloat(), isUninstall);
			break;
		case EModValueType_Weapon_ColdDown_Addend:
			unit->getWeapon()->ColdDown.add(this->value.asFloat(), isUninstall);
			break;
		case EModValueType_Weapon_ColdDown_Multiplier:
			unit->getWeapon()->ColdDown.mul(this->value.asFloat(), isUninstall);
			break;
		default:
			break;
		}
		break;

	}
}

void Modification::uninstall(Unit* unit)
{
	this->install(unit, true);
}

void Modification::setModification(Unit* unit, Value value)
{

}









