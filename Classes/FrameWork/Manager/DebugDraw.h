#pragma once
#include "GalaxyBase.h"

namespace cocosgalaxy
{
	class DebugDraw :public Layer
	{
	public:
		//µ¥ÀýÄ£Ê½
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
}


