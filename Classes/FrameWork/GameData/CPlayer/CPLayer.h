#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"

namespace cocosgalaxy
{
	class CPlayer : public CGameData
	{
	public:

		int money;
		int life;
		int wave;
		int wavecount;

		CPlayer();
		~CPlayer();


	};
}
