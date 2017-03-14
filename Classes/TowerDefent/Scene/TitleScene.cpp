#include "TitleScene.h"
#include "cocostudio/CocoStudio.h"
#include "UI/CocosGUI.h"
#include "LoadingScene.h"
#include "BattleScene.h"
#include "WorldMapScene.h"

#include "TextureManager.h"
#include "AnimateManager.h"
#include "UnitManager.h"
#include "WaveManager.h"
#include "ActorManager.h"
#include "WeaponManager.h"
#include "EffectManager.h"
#include "SkillManager.h"
#include "BehaviorManager.h"
#include "SpellCardManager.h"
#include "TowerCardManager.h"
#include "TDUnitCreator.h"
#include "Player.h"


USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}


Scene* TitleScene::createScene(){
 	auto scene = Scene::create();

	auto layer = TitleScene::create();
	scene->addChild(layer, 1);


	return scene;
}


bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto ui = dynamic_cast<Layout *>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/Title_Layer.ExportJson"));
	this->addChild(ui);

	//设置拉伸BG
	Sprite* bg = Sprite::create("UI/title_bg.png");
	bg->setAnchorPoint(Point(0, 0));
	Size size = Director::getInstance()->getVisibleSize();

	float scale = MAX(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
	bg->setScale(scale);
	ui->addChild(bg,-1);

	//获取控件
	auto bt_startgame = static_cast<Button*>(ui->getChildByName("bt_startgame"));
	auto bt_option = static_cast<Button*>(ui->getChildByName("bt_option"));
	auto bt_exit = static_cast<Button*>(ui->getChildByName("bt_exit"));
	auto img_logo = static_cast<Sprite*>(ui->getChildByName("img_logo"));
	auto label_version = static_cast<TextAtlas*>(ui->getChildByName("label_version"));

	bt_startgame->addClickEventListener(CC_CALLBACK_0(TitleScene::click_startgame, this));
	bt_option->addClickEventListener(CC_CALLBACK_0(TitleScene::click_option, this));
	bt_exit->addClickEventListener(CC_CALLBACK_0(TitleScene::click_exit, this));


	return true;
}


void TitleScene::click_startgame()
{
	log("TitleScene::click_startgame()");

	LoadingScene* loading = LoadingScene::create();


	loading->bindFinishFunction([=](){
		
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)WorldMapScene::createScene()));

	});

	loading->replaceScene(loading);
}


void TitleScene::click_option()
{

}

void TitleScene::click_exit()
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}





