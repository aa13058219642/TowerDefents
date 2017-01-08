#pragma once
#include "GalaxyBase.h"
#include "CUnit.h"

#define UTYPE_CUNIT 0

namespace cocosgalaxy
{
	class UnitCreator
	{
	public:
		UnitCreator();
		~UnitCreator();

		virtual CUnit* Create(string typeName, int tag = 0);
		virtual CUnit* Create(int typeID, int tag = 0);
	};
};
