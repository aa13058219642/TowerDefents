#pragma once
#include "CCost.h"

namespace cocosgalaxy
{
	class CCostPlayer :public CCost
	{
	public:
		CCostPlayer();
		~CCostPlayer();

		virtual bool isCanPay(CGameData* gamedata);
		virtual void payCost(CGameData* gamedata);


	};

}