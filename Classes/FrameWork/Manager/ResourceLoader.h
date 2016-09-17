#pragma once
#include "stdfax.h"

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();

	virtual void LoadResource(const vector<Name>& resNameList) = 0;
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName) = 0;
};

