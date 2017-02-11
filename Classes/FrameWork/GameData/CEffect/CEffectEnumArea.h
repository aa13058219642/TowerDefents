#pragma once
#include "CEffectResponse.h"

namespace cocosgalaxy
{
	class CEffectEnumArea : public CEffectResponse
	{
	public:
		CEffectEnumArea();
		CEffectEnumArea(unsigned int filter, int areaRadius, string applyEffect, CEffect* effect = nullptr, int parentID = -1);
		~CEffectEnumArea();

		virtual CEffect* clone();
		virtual void execute();

		int areaRadius;		//范围
		string applyEffect;	//应用效果名
		CEffect* effect;	//应用效果
		Point m_pos;		//应用坐标
	private:
	};
}
