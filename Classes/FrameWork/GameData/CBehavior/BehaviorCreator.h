#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"
#include "CCreator\CCreator.h"

namespace cocosgalaxy
{
	class BehaviorCreator : public CCreator
	{
	public:
		BehaviorCreator();
		~BehaviorCreator();

		virtual CGameData* Create(string className, string typeName = "");
		virtual CGameData* Create(int classHash, string typeName = "");
	};
};
