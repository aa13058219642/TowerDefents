#pragma once
#include "stdfax.h"
#include "GameMap.h"
#include "Unit.h"


class UnitLayer : public Layer
{
public:
	static UnitLayer* create();
	virtual bool init();
	virtual void update(float dt);

private:
	UnitLayer();

	bool onClick(Point pos);

	void DebugDraw();
	//void RunDelayAction(const std::function<void()>& func, float delayTime);
};



