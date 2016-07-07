#include "GameObjectTouchLayer.h"

GameObjectTouchLayer::GameObjectTouchLayer(){}
GameObjectTouchLayer::~GameObjectTouchLayer(){}

GameObjectTouchLayer* GameObjectTouchLayer::create(GameObjectLayer* layer)
{
	GameObjectTouchLayer* oprLayer = new GameObjectTouchLayer();
	if (oprLayer && oprLayer->init(layer))
	{
		oprLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(oprLayer);
	}
	return oprLayer;
}

bool GameObjectTouchLayer::init(GameObjectLayer* layer)
{
	if (!Layer::init())
		return false;
	this->m_gameObjectLayer = layer;

	//加载UI
	//auto UI = GUIReader::getInstance()->widgetFromJsonFile("Editor/ui_Editor.ExportJson");
	//this->addChild(UI);

	//关闭UI监听
	//UI->setTouchEnabled(false);

	//获取UI中的控件
	//auto bt_output = (Button*)Helper::seekWidgetByName(UI, "btn_output");

	//添加监听
	//Button* bt_output = new Button();
	//bt_output->addTouchEventListener(this, toucheventselector(GameObjectTouchLayer::bt_output_onClick));

	//设置监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event){
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		findClickTowerPos(pos);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void GameObjectTouchLayer::findClickTowerPos(Point pos)
{
	TowerBase* tower = (TowerBase*)m_gameObjectLayer->findGameObject(pos, GameObjectType::GameObject_Tower);

	if (tower != NULL)
	{
		log("towerPos:(%f,%f)", tower->getPos().x, tower->getPos().y);
		tower->upgrade();
	}
	else
	{
		
	}
}

//void GameObjectTouchLayer::bt_output_onClick(Ref*, TouchEventType type)
//{
//	if (type == TouchEventType::TOUCH_EVENT_ENDED)
//	{
//		//m_gameObjectLayer->findTower(pos);
//	}
//}