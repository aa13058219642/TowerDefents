#pragma once
#include"stdfax.h"
#include"GameObjectLayer.h"


class GameObjectTouchLayer : public Layer
{
public:
	GameObjectTouchLayer();
	~GameObjectTouchLayer();

	static GameObjectTouchLayer* create(GameObjectLayer* layer);
	virtual bool init(GameObjectLayer* layer);

	//void bt_output_onClick(Ref*, TouchEventType type);

private:
	GameObjectLayer* m_gameObjectLayer;
	void findClickTowerPos(Point pos);
};

