#pragma once
#include "GalaxyBase.h"

namespace cocosgalaxy
{
	typedef rapidjson::GenericValue<rapidjson::UTF8<char>>& JsonNode;

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();

		virtual void LoadResource() = 0;
		virtual void LoadResource(const vector<Name>& resNameList) = 0;
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName) = 0;
	};
}
