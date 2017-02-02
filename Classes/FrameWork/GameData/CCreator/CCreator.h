#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"

namespace cocosgalaxy
{

	class CCreator
	{
	public:
		CCreator();
		~CCreator();

		virtual CGameData* Create(string className, string typeName = "") = 0;
		virtual CGameData* Create(int classHash, string typeName = "") = 0;
	};
}
