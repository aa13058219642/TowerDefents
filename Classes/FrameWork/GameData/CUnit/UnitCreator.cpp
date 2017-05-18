#include "UnitCreator.h"
using namespace cocosgalaxy;

UnitCreator::UnitCreator()
{

}


UnitCreator::~UnitCreator()
{

}


CGameData* UnitCreator::Create(string className, string typeName)
{
	CGameData* data = nullptr;
	if (className == string("CUnit"))
	{
		data = Create(typeid(CUnit).hash_code(), typeName);
	}
	return data;
}

CGameData* UnitCreator::Create(int classHash, string typeName)
{
	CGameData* data;

	if (classHash == typeid(CUnit).hash_code())
		data = new CUnit();
	else
		data = nullptr;

	return data;
}