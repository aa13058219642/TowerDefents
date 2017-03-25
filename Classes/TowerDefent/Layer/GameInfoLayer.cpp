#include "GameInfoLayer.h"
#include "Player.h"
#include "TowerDefentShare.h"
#include "GameMap.h"

using namespace cocos2d;
using namespace cocos2d::ui;


GameInfoLayer::GameInfoLayer(){}

GameInfoLayer::~GameInfoLayer(){}

GameInfoLayer* GameInfoLayer::create()
{
	GameInfoLayer* layer = new GameInfoLayer();
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

bool GameInfoLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initUI();
	initListener();
	GameMap::getInstance()->UpdateNextWaveInfo();

	return true;
}

void GameInfoLayer::initUI()
{
	Widget* widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameInfo.ExportJson");
	this->addChild(widget);

	//载入控件 
	bt_CardInfo = static_cast<Button*>(widget->getChildByName("bt_CardInfo"));
	bt_Option = static_cast<Button*>(widget->getChildByName("bt_Option"));

	panel_TopLeft1 = static_cast<Layout*>(widget->getChildByName("panel_TopLeft1"));
	lab_Life = static_cast<Text*>(panel_TopLeft1->getChildByName("lab_Life"));
	lab_Money = static_cast<Text*>(panel_TopLeft1->getChildByName("lab_Money"));
	lab_Wave = static_cast<Text*>(panel_TopLeft1->getChildByName("lab_Wave"));

	panel_TopLeft2 = static_cast<Layout*>(widget->getChildByName("panel_TopLeft2"));
	bt_nextWave = static_cast<Button*>(panel_TopLeft2->getChildByName("bt_nextWave"));
	lab_nextWave = static_cast<Text*>(panel_TopLeft2->getChildByName("lab_nextWave"));

	ui_action_in = cocostudio::ActionManagerEx::getInstance()->getActionByName("GameInfo.ExportJson", "nextWave_in");
	ui_action_out = cocostudio::ActionManagerEx::getInstance()->getActionByName("GameInfo.ExportJson", "nextWave_out");
	isshow = true;

	int money = (int)Player::getInstance()->getMoney();
	lab_Money->setString(StringUtils::format("%d", money));
	isInUiAdmimate = false;
}

void GameInfoLayer::initListener()
{
	this->msgSubscribe(Message_Global);
	this->msgSubscribe(Message_GameInfoLayer);

	bt_CardInfo->addClickEventListener(CC_CALLBACK_0(GameInfoLayer::event_btCardInfo_click, this));
	bt_Option->addClickEventListener(CC_CALLBACK_0(GameInfoLayer::event_btOption_click, this));
	bt_nextWave->addClickEventListener(CC_CALLBACK_0(GameInfoLayer::event_btNextWave_click, this));
}

void GameInfoLayer::receive(const Message* message)
{
	if (message != nullptr)
	{
		if (message->keyword == "updateMoney")
		{
			int money = (int)Player::getInstance()->getMoney();
			lab_Money->setString(StringUtils::format("%d", money));
		}
		else if (message->keyword == "updateLife")
		{
			int life = (int)Player::getInstance()->getLife();
			lab_Life->setString(StringUtils::format("%d", life));
		}
		else if (message->keyword == "updateWave")
		{
			int wave = message->valueMap.at("wave").asInt();
			int wavecount = message->valueMap.at("waveCount").asInt();
			lab_Wave->setString(StringUtils::format("%d/%d", wave, wavecount));
		}
		else if (message->keyword == "updateNextWaveInfo")
		{
			string info = message->valueMap.at("value").asString();
			lab_nextWave->setString(info);

			isInUiAdmimate = true;
			ui_action_in->play(CallFunc::create([=](){isInUiAdmimate = false; ui_action_in->stop(); }));
			isshow = true;
		}
	}
}

void GameInfoLayer::event_btCardInfo_click()
{

}

void GameInfoLayer::event_btOption_click()
{

}

void GameInfoLayer::event_btNextWave_click()
{
	if (isInUiAdmimate)return;

	if (isshow)
	{
		isInUiAdmimate = true;
		ui_action_out->play(CallFunc::create([=](){isInUiAdmimate = false; ui_action_out->stop(); }));
		GameMap::getInstance()->SkipToNextWave();
	}
	else
	{
		isInUiAdmimate = true;
		ui_action_in->play(CallFunc::create([=](){isInUiAdmimate = false; ui_action_in->stop(); }));
	}
	isshow = !isshow;
}



