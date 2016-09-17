#pragma once
#include "stdfax.h"

class GameMapLayer : public Layer
{
public:
	GameMapLayer();
	~GameMapLayer();

	static GameMapLayer* create();
	virtual bool init();
	virtual void update(float dt);

};
