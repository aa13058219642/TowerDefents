#pragma once
#include "stdfax.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Message\MessageListener.h"

class GameInfoLayer : public Layer, MessageListener
{
public:
	GameInfoLayer();
	~GameInfoLayer();

	static GameInfoLayer* create();
	virtual bool init();
	virtual void receive(const Message* message);

	void event_btCardInfo_click();
	void event_btOption_click();
	void event_btNextWave_click();

private:
	void initUI();
	void initListener();

	cocos2d::ui::Layout* panel_TopLeft1;
	cocos2d::ui::Layout* panel_TopLeft2;
	cocos2d::ui::Text* lab_Life;
	cocos2d::ui::Text* lab_Money;
	cocos2d::ui::Text* lab_Wave;
	cocos2d::ui::Text* lab_nextWave;
	cocos2d::ui::Button* bt_nextWave;
	cocos2d::ui::Button* bt_CardInfo;
	cocos2d::ui::Button* bt_Option;

	cocostudio::ActionObject* ui_action_in;
	cocostudio::ActionObject* ui_action_out;

	bool isshow;
	bool isInUiAdmimate;
};
