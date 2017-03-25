#pragma once
#include "stdfax.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Message\MessageListener.h"

class WinLayer : public Layer, MessageListener
{
public:
	WinLayer();
	~WinLayer();

	static WinLayer* create();
	virtual bool init();
	virtual void update(float dt);

	virtual void receive(const Message* message);

	enum WinLayerState : int{ S_Normal, S_Hide, S_ShowLayer, S_ShowRank, S_ShowNumber };

private:
	int m_state;
	float money[5];
	float tmoney[5];
	int rank;

	cocos2d::ui::Text* lab_title;
	cocos2d::ui::Button* bt_red;
	cocos2d::ui::Button* bt_green;
	cocos2d::ui::ImageView* img_rank;
	cocos2d::ui::ImageView* img_rank2;
	cocos2d::Label* scoreLabel;


	void setData(string title, int rank, float money1, float money2, float money3, float money4);
	void show(float dt);
	void event_btRed_click();
	void event_btGreen_click();


};
