#include "TDUnitCreator.h"
//#include "BulletFactory.h"
#include "BulletManager.h"
using namespace cocosgalaxy;

TDUnitCreator::TDUnitCreator()
{

}


TDUnitCreator::~TDUnitCreator()
{

}


CGameData* TDUnitCreator::Create(string className, string typeName)
{
	CGameData* unit = UnitCreator::Create(className, typeName);
	if (unit == nullptr)
	{
		if (className == string("Bullet"))
		{
			unit = Create(typeid(Bullet).hash_code(), typeName);
		}
	}
	return unit;
}

CGameData* TDUnitCreator::Create(int classHash, string typeName)
{
	CGameData* data = UnitCreator::Create(classHash, typeName);

	if (data == nullptr)
	{
		if (classHash == typeid(Bullet).hash_code())
		{
			//data = BulletFactory::getInstance()->CreateBullet(typeName);
			data = BulletManager::getInstance()->CreateBullet(typeName);
		}
		else
			data = nullptr;
	}

	return data;
}