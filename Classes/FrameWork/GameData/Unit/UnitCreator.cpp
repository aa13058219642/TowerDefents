#include "UnitCreator.h"
using namespace cocosgalaxy;

UnitCreator::UnitCreator()
{

}


UnitCreator::~UnitCreator()
{

}


CUnit* UnitCreator::Create(string typeName, int tag)
{
	if (typeName == string("CUnit"))
	{
		return Create(UTYPE_CUNIT, tag);
	}
	return nullptr;
}

CUnit* UnitCreator::Create(int typeID, int tag)
{
	switch (typeID)
	{
	case UTYPE_CUNIT: return new CUnit();
	default: return nullptr;
	}
	return nullptr;
}