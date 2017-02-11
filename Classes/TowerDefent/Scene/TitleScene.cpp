#include "TitleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LoadingScene.h"
#include "BattleScene.h"

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

	auto ui = dynamic_cast<Layout *>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/Title_Layer.ExportJson"));
	this->addChild(ui);

	//设置拉伸BG
	Sprite* bg = Sprite::create("ui/title_bg.png");
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


	return true;
}


void TitleScene::click_startgame()
{
	log("TitleScene::click_startgame()");

	LoadingScene* loading = LoadingScene::createScene();

	ValueMap map;
	map["level"] = 1;

	loading->setBuffData(map);

	loading->bindBeginFunction([=](){
		Layer* layer = Layer::create();
		Size size = Director::getInstance()->getVisibleSize();
		layer->setPosition(Point(size.width / 2, size.height / 2));


		Sprite* sprite = Sprite::create("ui/loading.png");
		sprite->runAction(RepeatForever::create(EaseBackOut::create(RotateBy::create(1.0f,60))));
		sprite->setColor(Color3B(102, 204, 255));
		layer->addChild(sprite);

		Sprite* sprite2 = Sprite::create("ui/loading2.png");
		layer->addChild(sprite2);

		loading->addChild(layer);
	});

	loading->bindFinishFunction([=](){
		ValueMap map = loading->getBuffData();

		int level = map["level"].asInt();
		
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)BattleScene::createScene(level)));

		WaveManager::getInstance()->init();
	});

	std::queue<LoadingScene::LoadingCallback> list;
	list.push([](){  
		log("load TowerCardManager");

		TowerCardManager::getInstance()->LoadResource();
		std::vector<TowerCard> m_TowerCard;
		auto towerMgr = TowerCardManager::getInstance();

		vector<string> towercardList;
		towercardList.push_back("card000");
		towercardList.push_back("card001");
		towercardList.push_back("card002");
		towercardList.push_back("card003");
		towercardList.push_back("card004");
		towercardList.push_back("card005");
		towercardList.push_back("card006");
		towercardList.push_back("card007");

		TowerCard tcard;
		for (int i = 0; i < 8; i++)
		{
			tcard = *towerMgr->getTowerCard(towercardList[i]);
			tcard.gid = i;
			m_TowerCard.push_back(tcard);
		}

		Player::getInstance()->setTowerCard(m_TowerCard);
	});
	list.push([](){ 
		log("load SpellCardManager"); 
	
		SpellCardManager::getInstance()->LoadResource();

		std::vector<SpellCard> m_SpellCard;
		auto spellMgr = SpellCardManager::getInstance();

		vector<string> spellcardList;
		spellcardList.push_back("Damage_Add_I");
		spellcardList.push_back("Range_Add_I");
		spellcardList.push_back("ColdDown_Div_I");
		spellcardList.push_back("TargetCount_Add_I");
		spellcardList.push_back("CriticalChance_Add_I");
		spellcardList.push_back("MaxDamage_Add_I");
		spellcardList.push_back("CriticalMultiplier_Add_I");
		spellcardList.push_back("BoomRange_Add_I");

		SpellCard scard;
		for (int i = 0; i < 8; i++)
		{
			scard = *spellMgr->getSpellCard(spellcardList[i]);
			scard.gid = i;
			m_SpellCard.push_back(scard);
		}

		Player::getInstance()->setSpellCard(m_SpellCard);

	});
	list.push([](){ 
		log("load Player");  
	
		Player* player = Player::getInstance();
		player->reset();
		player->setMoney(2000);
		player->setLife(20);

	});
	list.push([](){ log("load UnitManager");  UnitManager::getInstance()->init(new TDUnitCreator()); });
	list.push([](){ log("load BehaviorManager");  BehaviorManager::getInstance()->init(); });
	list.push([](){ log("load EffectManager");  	EffectManager::getInstance()->init(); });
	list.push([](){ 
		log("load TextureManager");  
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		textureList.push_back("texture/UI/TowerSelectLayer.plist");
		textureList.push_back("texture/UI/TowerInfoLayer.plist");
		textureList.push_back("texture/UI/GameMapInfoLayer.plist");
		textureList.push_back("texture/effect/effect_000.plist");
		textureList.push_back("texture/Tower/Tower_000.plist");
		textureList.push_back("texture/Tower/Tower_001.plist");
		textureList.push_back("texture/Tower/Tower_006.plist");
		TextureManager::getInstance()->LoadResource(textureList);
	});
	list.push([](){ log("load SkillManager");  SkillManager::getInstance()->LoadResource(); });
	list.push([](){ log("load BehaviorManager");  BehaviorManager::getInstance()->LoadResource(); });
	list.push([](){ log("load AnimateManager");  AnimateManager::getInstance()->LoadResource(); });
	list.push([](){ log("load ActorManager");  ActorManager::getInstance()->LoadResource(); });
	list.push([](){ log("load WeaponManager"); WeaponManager::getInstance()->LoadResource(); });
	list.push([](){ log("load EffectManager"); EffectManager::getInstance()->LoadResource(); });

	loading->setLambdaLoadList(list);

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)loading));
}

void TitleScene::onExit()
{
	Layer::onExit();
	log("TitleScene::onExit()");

}







