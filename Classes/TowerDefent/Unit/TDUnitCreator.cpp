#include "TDUnitCreator.h"
#include "BulletFactory.h"
using namespace cocosgalaxy;

TDUnitCreator::TDUnitCreator()
{

}


TDUnitCreator::~TDUnitCreator()
{

}


CUnit* TDUnitCreator::Create(string typeName, int tag)
{
	CUnit* unit = UnitCreator::Create(typeName, tag);
	if (unit != nullptr)
		return unit;

	if (typeName == string("Bullet"))
	{
		return Create(UTYPE_BULLET, tag);
	}
	return nullptr;
}

CUnit* TDUnitCreator::Create(int typeID, int tag)
{
	CUnit* unit = UnitCreator::Create(typeID, tag);
	if (unit != nullptr)
		return unit;

	switch (typeID)
	{
	case UTYPE_BULLET: return BulletFactory::getInstance()->CreateBullet(tag);
	default: return nullptr;
	}
	return nullptr;
}