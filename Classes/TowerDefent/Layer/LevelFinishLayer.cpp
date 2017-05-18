#include "LevelFinishLayer.h"
#include "TowerDefentShare.h"
#include "LoadingScene.h"
#include "PrepareScene.h"
#include "WorldMapScene.h"
#include "TextureManager.h"


USING_NS_CC;
using namespace std;
using namespace cocostudio;
using namespace cocos2d::ui;

LevelFinishLayer::LevelFinishLayer(){}

LevelFinishLayer::~LevelFinishLayer(){}

LevelFinishLayer* LevelFinishLayer::create()
{
	LevelFinishLayer* layer = new LevelFinishLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(layer);
	}
	return layer;
}

bool LevelFinishLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_state = S_Hide;

	auto ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Layer_LevelFinish.ExportJson"));
	this->addChild(ui);

	//获取控件
	lab_title = static_cast<Text*>(ui->getChildByName("lab_title"));
	bt_red = static_cast<Button*>(ui->getChildByName("bt_red"));
	bt_green = static_cast<Button*>(ui->getChildByName("bt_green"));
	img_win = static_cast<ImageView*>(ui->getChildByName("img_win"));
	img_defeat = static_cast<ImageView*>(ui->getChildByName("img_defeat"));
	img_rank = static_cast<ImageView*>(ui->getChildByName("img_rank"));
	img_rank2 = static_cast<ImageView*>(img_rank->clone());
	img_rank2->setPosition(img_rank->getPosition());
	ui->addChild(img_rank2);

	bt_red->addClickEventListener(CC_CALLBACK_0(LevelFinishLayer::event_btRed_click, this));
	bt_green->addClickEventListener(CC_CALLBACK_0(LevelFinishLayer::event_btGreen_click, this));

	MessageListener::msgSubscribe(Message_LevelFinishLayer);

	//atlasLabel->
	scoreLabel = Label::createWithCharMap("fonts/TowerInfo_Number.png", 24, 42, ' ');
	scoreLabel->setHorizontalAlignment(TextHAlignment::RIGHT);
	scoreLabel->setPosition(Point(806, 418));
	ui->addChild(scoreLabel);

	this->scheduleUpdate();

	return true;
}

void LevelFinishLayer::update(float dt){

	if (m_state == S_Hide || m_state == S_Normal)
	{
		return;
	}
	else if (m_state == S_ShowLayer)
	{
		return;
	}
	else if (m_state == S_ShowRank)
	{
		log("rank1");


		img_rank->setScale(3);
		img_rank->setOpacity(0);
		img_rank->setVisible(true);

		auto act1 = ScaleTo::create(0.75f, 1.0f);
		auto act2 = FadeIn::create(0.75f);
		auto act3 = Spawn::create(act1, act2, NULL);
		auto act = EaseSineIn::create(act3);
		auto act11 = CallFunc::create([&](){
			img_rank2->setOpacity(255);
			img_rank2->setVisible(true);

		});
		img_rank->runAction(Sequence::create(act, act11, NULL));


		img_rank2->setScale(1);
		img_rank2->setVisible(false);

		auto act4 = ScaleTo::create(0.5f, 2.0f);
		auto act5 = FadeOut::create(0.5f);
		auto act6 = Spawn::create(act4, act5, NULL);
		auto act7 = EaseSineIn::create(act6);
		auto act8 = DelayTime::create(1.0f);
		auto act9 = CallFunc::create([&](){
			img_rank2->setVisible(false);
			m_state = S_ShowNumber;

		});
		auto act10 = Sequence::create(act8, act7, act9, NULL);
		img_rank2->runAction(act10);

		m_state = S_Normal;
		return;
	}
	else if (m_state == S_ShowNumber)
	{

		float k = 30;

		if (tmoney[0] < money[0])
		{
			tmoney[0] += money[0] / k;
		}
		else if (tmoney[1] < money[1])
		{
			tmoney[0] = money[0];
			tmoney[1] += money[1] / k;
		}
		else if (tmoney[2] < money[2])
		{
			tmoney[1] = money[1];
			tmoney[2] += money[2] / k;
		}
		else if (tmoney[3] < money[3])
		{
			tmoney[2] = money[2];
			tmoney[3] += money[3] / k;
		}
		else if (tmoney[4] < money[4])
		{
			tmoney[3] = money[3];
			tmoney[4] += money[4] / k;
		}
		else
		{
			tmoney[4] = money[4];
			m_state = S_Normal;
		}
		string str = StringUtils::format("+%d\n+%d\n+%d\n+%d\n----------\n%d", (int)tmoney[0], (int)tmoney[1], (int)tmoney[2], (int)tmoney[3], (int)tmoney[4]);
		scoreLabel->setString(str);
	}

}

void LevelFinishLayer::receive(const Message* message)
{
	if (message->keyword == "show")
	{
		auto map = message->valueMap;
		bool iswin = map.at("iswin").asBool();
		if (iswin)
		{
			setData(map.at("world").asInt(),
				map.at("level").asInt(),
				map.at("title").asString(),
				map.at("rank").asInt(),
				map.at("money1").asFloat(),
				map.at("money2").asFloat(),
				map.at("money3").asFloat(),
				map.at("money4").asFloat());
			this->scheduleOnce(schedule_selector(LevelFinishLayer::showForWin), 3.0f);
		}
		else
		{
			this->scheduleOnce(schedule_selector(LevelFinishLayer::showForDefeat), 0.1f);
		}
	}
}


void LevelFinishLayer::showForWin(float dt)
{
	Size visiblesize = Director::getInstance()->getVisibleSize();
	this->setPosition(Point(0, -1000));

	CallFunc* callfunc = CallFunc::create([&](){
		m_state = S_ShowRank;
	});

	this->runAction(Sequence::create(MoveTo::create(0.2f, Point(0, 0)), callfunc, NULL));
	img_rank->setVisible(false);
	img_rank2->setVisible(false);
	img_win->setVisible(true);
	img_defeat->setVisible(false);
	this->setVisible(true);
	m_state = S_ShowLayer;
}

void LevelFinishLayer::showForDefeat(float dt)
{
	Size visiblesize = Director::getInstance()->getVisibleSize();
	this->setPosition(Point(0, -1000));

	CallFunc* callfunc = CallFunc::create([&](){
		m_state = S_Normal;
	});

	this->runAction(Sequence::create(MoveTo::create(0.2f, Point(0, 0)), callfunc, NULL));
	img_rank->setVisible(false);
	img_rank2->setVisible(false);
	img_win->setVisible(false);
	img_defeat->setVisible(true);
	this->setVisible(true);	
	m_state = S_ShowLayer;
}


void LevelFinishLayer::setData(int world, int level, string title, int rank, float money1, float money2, float money3, float money4)
{
	m_world = world;
	m_level = level;
	this->rank = rank;
	money[0] = money1;
	money[1] = money2;
	money[2] = money3;
	money[3] = money4;
	money[4] = money1 + money2 + money3 + money4;
	tmoney[0] = tmoney[1] = tmoney[2] = tmoney[3] = tmoney[4] = 0;

	lab_title->setString(title);
	string sname = StringUtils::format("star%d.png", rank);
	img_rank->loadTexture(sname, Widget::TextureResType::PLIST);
	img_rank2->loadTexture(sname, Widget::TextureResType::PLIST);

	scoreLabel->setString(StringUtils::format("+%d\n+%d\n+%d\n+%d\n----------\n%d", 0,0,0,0,0));
}


void LevelFinishLayer::event_btRed_click()
{
	LoadingScene* loading = LoadingScene::create();

	ValueMap map;
	map["world"] = m_world;
	map["level"] = m_level;
	loading->setData(map);

	std::queue<LoadingScene::LoadingCallback> list;
	list.push([](){
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		textureList.push_back("texture/UI/TowerSelectLayer.plist");
		textureList.push_back("texture/UI/TowerInfoLayer.plist");
		textureList.push_back("texture/UI/GameMapInfoLayer.plist");
		textureList.push_back("texture/icon/Icon_000.plist");
		TextureManager::getInstance()->LoadResource(textureList);
	});
	list.push([](){ TowerCardManager::getInstance()->LoadResource(); });
	list.push([](){ SpellCardManager::getInstance()->LoadResource(); });
	list.push([](){ WeaponManager::getInstance()->LoadResource(); });
	loading->setLambdaLoadList(list);

	loading->bindFinishFunction([=](){
		PrepareScene* scene = PrepareScene::create();
		ValueMap map = loading->getData();
		if (scene->initData(map["world"].asInt(), map["level"].asInt()))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)scene));
		}
	});

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)loading));
}

void LevelFinishLayer::event_btGreen_click()
{
	LoadingScene* loading = LoadingScene::create();
	loading->bindFinishFunction([=](){
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		TextureManager::getInstance()->LoadResource(textureList);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)WorldMapScene::createScene()));

	});
	loading->replaceScene(loading);
}






