#pragma once
#include "stdfax.h"

class Helper
{
public:
	~Helper();
	static int hashCode(string str);

	/*return [min,max) */
	static float rand(float min, float max);
private:
	Helper();
};

