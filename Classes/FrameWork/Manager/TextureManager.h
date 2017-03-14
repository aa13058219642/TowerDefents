#pragma once
#include "GalaxyBase.h"
#include "ResourceLoader.h"

namespace cocosgalaxy
{
	class TextureManager :public ResourceLoader
	{
	public:
		//µ¥ÀýÄ£Ê½
		static TextureManager* getInstance();

		virtual void LoadResource();
		virtual void LoadResource(const vector<Name>& resNameList);
		virtual void FreeAllResource();
		virtual void FreeResource(const vector<Name>& resName);

		void LoadExtraTexture();

	private:
		TextureManager();
		static TextureManager* p_myinstance;

	};
}


