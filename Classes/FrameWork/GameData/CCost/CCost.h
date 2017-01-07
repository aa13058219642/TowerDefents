#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"

namespace cocosgalaxy
{
	typedef int CostRes_1;
	typedef int CostRes_2;
	typedef int CostRes_3;
	typedef int CostRes_Gold;


	class CCost :public CGameData
	{
	public:
		virtual bool isCanPay(CGameData* gamedata);
		virtual void payCost(CGameData* gamedata);

		CCost();
		~CCost();
	};

}