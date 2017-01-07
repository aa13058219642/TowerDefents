#pragma once
#include "stdfax.h"

class PrepareScene : public Layer
{
public:
	PrepareScene();
	~PrepareScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PrepareScene);

};
