#include "PrepareScene.h"

PrepareScene::PrepareScene(){}

PrepareScene::~PrepareScene(){}


Scene* PrepareScene::createScene(){
 	auto scene = Scene::create();

	auto layer = PrepareScene::create();
	scene->addChild(layer, 1);


	return scene;
}


bool PrepareScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	cocos2d::ui::Widget* widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/PrepareLayer.ExportJson");
	this->addChild(widget);





	return true;
}










