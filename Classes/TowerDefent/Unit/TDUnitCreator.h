#pragma once
#include "stdfax.h"

#define UTYPE_BULLET 1

namespace cocosgalaxy
{
	namespace EUnitType
	{
		const UnitType Tower = 1 << 4;
		const UnitType Monster = 1 << 5;
		const UnitType Bullet = 1 << 6;
	}

	typedef unsigned int BulletType;
	namespace EBulletType
	{
		const BulletType Ball = 0;
		const BulletType Missile = 1;
	};

};



class TDUnitCreator : public cocosgalaxy::UnitCreator
{
public:
	TDUnitCreator();
	~TDUnitCreator();

	virtual CUnit* Create(string typeName, int tag = 0);
	virtual CUnit* Create(int typeID, int tag = 0);
};
