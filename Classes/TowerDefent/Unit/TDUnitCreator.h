#pragma once
#include "stdfax.h"

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

	virtual CGameData* Create(string className, string typeName = "");
	virtual CGameData* Create(int classHash, string typeName = "");
};
