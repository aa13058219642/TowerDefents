#pragma once
#include "CCost.h"
#include "Ability.h"
namespace cocosgalaxy
{
	class CCostUnit : public CCost
	{
	public:
		CCostUnit();
		~CCostUnit();

		virtual bool isCanPay(CGameData* gamedata);
		virtual void payCost(CGameData* gamedata);

		Ability<float> HP;
		Ability<float> MP;
		Ability<float> AP;
		Ability<float> Speed;



		//private:
	};

}