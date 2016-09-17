#pragma once
#include "stdfax.h"

class DebugDraw :public Layer
{
public:
	//����ģʽ
	static DebugDraw* getInstance();
	static bool isDebug;
	bool Draw();

	DrawNode* getDrawNode();
	Label* getLabel();
private:
	DebugDraw();
	static DebugDraw* p_myinstance;

	bool init();

	DrawNode* debugDrawNode;
	Label* debugLabel;
};



