#pragma once
#include "stdfax.h"
#include "GameMap.h"
#include "CUnit.h"


class UnitLayer : public Layer
{
public:
	static UnitLayer* create();
	virtual bool init();
	virtual void update(float dt);

private:
	UnitLayer();
	~UnitLayer();

	bool onClick(Point pos);

	void DebugDraw();
};



