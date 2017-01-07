#pragma once
#include "GalaxyBase.h"

namespace cocosgalaxy
{
	class GalaxyHelper
	{
	public:
		~GalaxyHelper();
		static int hashCode(string str);

		/*return [min,max) */
		static float rand(float min, float max);
	private:
		GalaxyHelper();
	};
}

