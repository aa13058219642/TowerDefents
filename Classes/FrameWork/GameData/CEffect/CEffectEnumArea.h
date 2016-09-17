#pragma once
#include "CEffectResponse.h"

class CEffectEnumArea : public CEffectResponse
{
public:
	CEffectEnumArea(unsigned int filter, int areaRadius, string applyEffect, CEffect* effect = nullptr, int parentID = -1);
	~CEffectEnumArea();

	virtual CEffect* clone();
	virtual void execute();

private:
	int areaRadius;
	string applyEffect;
	CEffect* effect;
	Point m_pos;
};

