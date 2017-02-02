#pragma once
#include "CEffectResponse.h"

namespace cocosgalaxy
{
	class CEffectLaunchMissile : public CEffectResponse
	{
	public:
		CEffectLaunchMissile();
		CEffectLaunchMissile(string className, string typeName);
		~CEffectLaunchMissile();

		virtual CEffect* clone();
		virtual void execute();

		string className;	//类名
		string typeName;	//子类标签(参数)
	private:
	};
}
