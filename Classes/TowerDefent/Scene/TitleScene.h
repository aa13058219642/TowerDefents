#pragma once
#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
	TitleScene();
	~TitleScene();

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	CREATE_FUNC(TitleScene);

	void click_startgame();

};
