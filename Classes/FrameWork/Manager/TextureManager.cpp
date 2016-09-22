#include "TextureManager.h"


TextureManager* TextureManager::p_myinstance = nullptr;

TextureManager::TextureManager()
{

}

TextureManager* TextureManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new TextureManager();
	}
	return p_myinstance;
}



void TextureManager::LoadResource(const vector<Name>& resNameList)
{
	FileUtils* fileUtils = FileUtils::getInstance();
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	

	for (auto& var : resNameList)
	{
		CCASSERT(!fileUtils->isFileExist(var.substr(var.find_last_of('/')+1)), string("Texture [" + var + "] NOT found").c_str());
		frameCache->addSpriteFramesWithFile(var);
	}
	//plist = StringUtils::format("texture/scene_battle_%03d.plist", 0);
	//if (fileUtils->isFileExist(plist))

	//frameCache->getSpriteFrameByName("")->getTexture();
	//Label* l = Label::createWithCharMap("");

}




void TextureManager::FreeAllResource()
{
	SpriteFrameCache::getInstance()->destroyInstance();
}

void TextureManager::FreeResource(const vector<Name>& resName)
{
	//std::string plist;
	//FileUtils* fileUtils = FileUtils::getInstance();
	//SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	//switch (type)
	//{
	//case Texture_Battle:
	//	for (int i = 0;; i++)
	//	{
	//		plist = StringUtils::format("scene_battle_%03d.plist", i);
	//		if (fileUtils->isFileExist(plist))
	//			frameCache->removeSpriteFramesFromFile(plist);
	//		else
	//			break;
	//	}
	//	break;
	//case Texture_UI:
	//	break;
	//default:
	//	break;
	//}
}






