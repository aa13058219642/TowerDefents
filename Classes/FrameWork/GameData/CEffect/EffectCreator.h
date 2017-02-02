#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"
#include "CCreator\CCreator.h"

namespace cocosgalaxy
{
	class EffectCreator : public CCreator
	{
	public:
		EffectCreator();
		~EffectCreator();

		virtual CGameData* Create(string className, string typeName = "");
		virtual CGameData* Create(int classHash, string typeName = "");
	};
};
