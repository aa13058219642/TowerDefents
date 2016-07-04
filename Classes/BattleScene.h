#pragma once
#include "stdfax.h"

class BattleScene : public Layer
{
public:
	BattleScene();
	~BattleScene();

	CREATE_FUNC(BattleScene);
	static Scene* createScene(int level, bool isDebug = false);
	static BattleScene* create(bool isDebug = false);	
	virtual bool init();
	virtual void update(float dt);

	//virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);//重写draw方法，绘制debug用数据
	void setDebug(bool isDebug);

	DrawNode* drawNode;

private:
	bool m_isDebug; //当前为调试模式

	//void onDraw(const Mat4 &transform, bool transformUpdated);	//
	//CustomCommand _customCommand;
};
