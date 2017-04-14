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

	void event_btNextWave_click();
	void event_btTabShow_click();
	void event_cbPause_click();
	void event_cbSpeedUp_click();
	void event_cbSoundEffect_click();
	void event_cbMusic_click();
	void event_cbHome_click();

private:
	void initUI();
	void initListener();

	cocos2d::ui::Layout* panel_TopLeft1;
	cocos2d::ui::Layout* panel_TopLeft2;
	cocos2d::ui::Layout* panel_TopRight;
	cocos2d::ui::Layout* panel_BottomLeft;
	cocos2d::ui::Text* lab_Life;
	cocos2d::ui::Text* lab_Money;
	cocos2d::ui::Text* lab_Wave;
	cocos2d::ui::Text* lab_nextWave;
	cocos2d::ui::Button* bt_nextWave;
	cocos2d::ui::Button* bt_tabShow;
	cocos2d::ui::CheckBox* cb_pause;
	cocos2d::ui::CheckBox* cb_speedup;
	cocos2d::ui::CheckBox* cb_soundeffect;
	cocos2d::ui::CheckBox* cb_music;
	cocos2d::ui::CheckBox* cb_home;



	cocostudio::ActionObject* ui_action_in;
	cocostudio::ActionObject* ui_action_out;

	bool isshow;
	bool isInUiAdmimate;
};
