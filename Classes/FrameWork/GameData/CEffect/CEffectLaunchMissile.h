#pragma once
#include "CEffectResponse.h"

namespace cocosgalaxy
{
	class CEffectLaunchMissile : public CEffectResponse
	{
	public:
		CEffectLaunchMissile(int BulletID);
		~CEffectLaunchMissile();

		virtual CEffect* clone();
		virtual void execute();



	private:
		int BulletID;

	};
}
