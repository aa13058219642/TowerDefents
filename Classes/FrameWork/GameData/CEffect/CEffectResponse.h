#pragma once
#include "CEffect.h"

namespace cocosgalaxy
{
	class CEffectResponse : public CEffect
	{
	public:
		CEffectResponse();
		~CEffectResponse();

		virtual CEffect* clone() = 0;
		virtual void execute() = 0;


		float chance;	//发动几率
	private:


	};
}
