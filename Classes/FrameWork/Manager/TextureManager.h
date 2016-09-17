#pragma once
#include "stdfax.h"
#include "EnumConst.h"
#include "ResourceLoader.h"

class TextureManager :public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static TextureManager* getInstance();

	//void LoadTexture(ETextureType type);
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

private:
	TextureManager();
	static TextureManager* p_myinstance;

};



