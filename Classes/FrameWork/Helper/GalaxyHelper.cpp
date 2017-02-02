#include "GalaxyHelper.h"
using namespace cocosgalaxy;

int helper::hashCode(std::string str) {
	int h = 0;

	int off = 0;
	char val[32] = {0};
	int len = str.size();

	for (int i = 0; i < len; i++) {
		h = 31 * h + str.c_str()[i];
	}
	return h;
}


float helper::rand(float min, float max)
{
	return rand_0_1()*(max - min + 1) + min;
}
