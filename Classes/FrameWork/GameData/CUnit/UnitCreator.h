#pragma once
#include "GalaxyBase.h"
#include "CCreator\CCreator.h"
#include "CUnit.h"

namespace cocosgalaxy
{
	class UnitCreator : public CCreator
	{
	public:
		UnitCreator();
		~UnitCreator();

		virtual CGameData* Create(string className, string typeName = "");
		virtual CGameData* Create(int classHash, string typeName = "");
	};
};
