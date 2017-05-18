#pragma once
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "GridPageView.h"
#include "Message\MessageListener.h"
#include "TowerCardManager.h"
#include "SpellCardManager.h"



class CardGridItem :public cocos2d::ui::GridItem
{
public:
	CardGridItem(){};
	~CardGridItem(){};
	CREATE_FUNC(CardGridItem);

	virtual bool init();
	virtual void onTouchEnded(Touch* touch, Event* event);
	CardGridItem* clone();
	void setIcon(string iconname);

	enum CardGridItemType{empty, tower,spell};

	int type;
	const TowerCard* tcard;
	const SpellCard* scard;
	string iconName;
	bool isChoose;
};


class PrepareScene : public cocos2d::Scene,MessageListener
{
public:
	PrepareScene();
	~PrepareScene();

	virtual bool init();
	CREATE_FUNC(PrepareScene);

	virtual void receive(const Message* message);
	bool initData(int wrold, int level);

private:
	void initUI();
	void initListener();
	void initPlayerData();
	bool initMapData(int wrold, int level);

	void event_btGO_click();
	void event_btReturn_click();
	void event_btChoose_click();

	string m_title;
	int m_level;
	int m_wrold;
	float BaseMoney;
	float AddMoney;
	float AwardMoney;

	CardGridItem* curItem;
	Vector<CardGridItem*> itemlist;


	cocos2d::Layer* actorLayer;
	cocos2d::Sprite* gridItem_selected1;
	cocos2d::Sprite* gridItem_selected2;

	cocos2d::ui::CheckBox* cb_tabbt_card;
	cocos2d::ui::CheckBox* cb_tabbt_map;
	cocos2d::ui::Button* bt_return;
	cocos2d::ui::Button* bt_go;
	cocos2d::ui::Button* bt_addmoney;
	cocos2d::ui::Text* label_money;
	cocos2d::ui::Text* label_cost;
	cocos2d::ui::Layout* panel_selectionCard;
	cocos2d::ui::ImageView* image_dialogBG;
	cocos2d::ui::Text* title0;

	cocos2d::ui::Layout* panel_card_left;
	cocos2d::ui::Text* title1;
	cocos2d::ui::Layout* panel_gridview1;
	cocos2d::ui::GridPageView* gridview1;

	cocos2d::ui::Layout* panel_card_right;
	cocos2d::ui::Text* title2;
	cocos2d::ui::ImageView* image_card;
	cocos2d::ui::Text* cardinfo;
	cocos2d::ui::Button* bt_choose;

	cocos2d::ui::Layout* panel_map_left;
	cocos2d::ui::Text* title3;
	cocos2d::ui::ImageView* image_map;

	cocos2d::ui::Layout* panel_map_right;
	cocos2d::ui::Text* title4;
	cocos2d::ui::Layout* panel_gridview2;
	cocos2d::ui::GridPageView* gridview2;

};
