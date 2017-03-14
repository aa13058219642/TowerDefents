#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "UI/CocosGUI.h"



class WorldMapScene : public cocos2d::Layer
{
public:
	WorldMapScene();
	~WorldMapScene();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WorldMapScene);

	void LoadResource();
	void initListView();
	void showMap(int index);

	void event_lp_click(cocos2d::Ref* sender);
	void event_world_click(cocos2d::Ref* sender);
	void event_btReturn_click();


	struct LevelPoint
	{
		int id;
		int x, y;
		std::vector<int> next;
		std::string name;
		std::string info;
	};

	struct WorldData
	{
		int ID;
		std::string name;
		std::string bg;
		std::string icon;
		std::vector<LevelPoint> levelpoint;
	};

private:
	int curIndex;
	std::vector<WorldData> worldData;
	cocos2d::Layer* worldLayer;
	cocos2d::Layer* lp_layer;
	cocos2d::ui::Text* worldname;
	cocos2d::ui::ListView* listview;
};
