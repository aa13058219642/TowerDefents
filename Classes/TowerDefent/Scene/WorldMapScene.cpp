#include "WorldMapScene.h"
#include "TowerDefentShare.h"
#include "LoadingScene.h"
#include "PrepareScene.h"
#include "TitleScene.h"
#include "TextureManager.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;
using namespace cocos2d::ui;

WorldMapScene::WorldMapScene(){}

WorldMapScene::~WorldMapScene(){}


Scene* WorldMapScene::createScene(){
 	auto scene = Scene::create();

	auto layer = WorldMapScene::create();
	scene->addChild(layer, 1);


	return scene;
}


bool WorldMapScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto ui = dynamic_cast<Layout *>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("WorldMapLayer.ExportJson"));
	this->addChild(ui);

	//设置拉伸BG
	Sprite* bg = Sprite::create("ui_bg.png");
	bg->setColor(Color3B(0, 204, 255));
	bg->setAnchorPoint(Point(0, 0));
	Size size = Director::getInstance()->getVisibleSize();
	float scale = MAX(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
	bg->setScale(scale);
	ui->addChild(bg, -1);

	//获取控件
	Layout* panel_left = static_cast<Layout*>(ui->getChildByName("panel_left"));
	Layout* panel_right = static_cast<Layout*>(ui->getChildByName("panel_right"));
	auto br_return = static_cast<Button*>(ui->getChildByName("br_return"));
	br_return->addClickEventListener(CC_CALLBACK_0(WorldMapScene::event_btReturn_click, this));

	listview = static_cast<ListView*>(panel_left->getChildByName("listview"));

	worldname = static_cast<Text*>(panel_right->getChildByName("wroldname"));

	worldLayer = Layer::create();
	worldLayer->setContentSize(Size(880, 680));
	worldLayer->setPosition(Point(440,375));
	panel_right->addChild(worldLayer, -1);

	cocos2d::ui::Scale9Sprite* dialog = cocos2d::ui::Scale9Sprite::create("dialog_b.png");
	dialog->setContentSize(worldLayer->getContentSize());
	worldLayer->addChild(dialog);

	lp_layer = Layer::create();
	lp_layer->setPosition(Point(-worldLayer->getContentSize().width / 2, -worldLayer->getContentSize().height / 2));

	worldLayer->addChild(lp_layer, 100);


	//listview

	LoadResource();
	initListView();
	return true;
}

void WorldMapScene::LoadResource()
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> resNameList;

	FileUtils* fin = FileUtils::getInstance();
	Data data = fin->getDataFromFile("data/WorldMap.json");
	CCASSERT(!data.isNull(), "[WorldMap.json] NOT found");

	string str = string((char*)data.getBytes(), data.getSize());
	rapidjson::Document root;
	root.Parse<0>(str.c_str());
	CCASSERT(root.IsObject() && root.HasMember("WroldMap") && root["WroldMap"].IsArray(), "illegal [WroldMap.json]: WroldMap Data error");

	float scale = 1 / Director::getInstance()->getContentScaleFactor();

	bool fullLoad = true;
	if (resNameList.size() != 0)fullLoad = false;
	int size = root["WroldMap"].Size();
	for (int i = 0; i < size; i++)
	{
		JsonNode jNode = root["WroldMap"][i];
		string name = jNode["name"].GetString();
		if (fullLoad || std::find(resNameList.begin(), resNameList.end(), name) != resNameList.end())
		{
			WorldData data;
			if (jNode.HasMember("ID"))				data.ID = jNode["ID"].GetInt();
			if (jNode.HasMember("name"))			data.name = jNode["name"].GetString();
			if (jNode.HasMember("bg"))				data.bg = jNode["bg"].GetString();
			if (jNode.HasMember("icon"))			data.icon = jNode["icon"].GetString();

			if (jNode.HasMember("level") && jNode["level"].IsArray())
			{
				JsonNode levelNode = jNode["level"];
				int s = levelNode.Size();
				for (int j = 0; j < s; j++)
				{
					LevelPoint lp;
					if (levelNode[j].HasMember("id"))			lp.id = levelNode[j]["id"].GetInt();
					if (levelNode[j].HasMember("x"))			lp.x = levelNode[j]["x"].GetInt();
					if (levelNode[j].HasMember("y"))			lp.y = levelNode[j]["y"].GetInt();
					if (levelNode[j].HasMember("name"))			lp.name = levelNode[j]["name"].GetString();
					if (levelNode[j].HasMember("info"))			lp.info = levelNode[j]["info"].GetString();

					if (levelNode[j].HasMember("next") && levelNode[j]["next"].IsArray())
					{
						int ss = levelNode[j]["next"].Size();
						for (int k = 0; k < ss; k++)
						{
							lp.next.push_back(levelNode[j]["next"][k].GetInt());
						}
					}

					data.levelpoint.push_back(lp);
				}
			}
			worldData.push_back(data);
		}
	}

}

void WorldMapScene::initListView()
{
	//listview = cocos2d::ui::ListView::create();
	//listview->setPosition(Point(100, 100));
	//listview->setContentSize(Size(550, 750));
	//listview->setInnerContainerSize(Size(290, 650));
	listview->setDirection(ListView::Direction::VERTICAL);
	listview->setScrollBarEnabled(false);
	listview->setGravity(ListView::Gravity::CENTER_VERTICAL);
	listview->setInnerContainerPosition(Point(32,0));
	listview->setInnerContainerSize(Size(250, 600));
	listview->setItemsMargin(10);
	//this->addChild(listview);

	float scale = Director::getInstance()->getContentScaleFactor();

	int size = worldData.size();
	for (int i = 0; i < size; i++)
	{
		std::string name = std::string("worldmap/" + worldData[i].icon);
		auto item = Button::create(name);
		item->setScale(scale);
		item->setTag(i);
		item->addClickEventListener(CC_CALLBACK_1(WorldMapScene::event_world_click, this));
		item->setZoomScale(0);
		listview->addChild(item);

	}

	auto tex = Director::getInstance()->getTextureCache()->addImage("worldbutton_select.png");
	auto sf = SpriteFrame::createWithTexture(tex, Rect(Point::ZERO, tex->getContentSizeInPixels()));
	SpriteFrameCache::getInstance()->addSpriteFrame(sf, "worldbutton_select.png");

	Sprite* s = Sprite::createWithSpriteFrameName("worldbutton_select.png");
	Button* button = static_cast<Button*>(listview->getItem(0));
	Size sizes = button->getContentSize();
	s->setPosition(Point(sizes.width / 2, sizes.height / 2));
	button->addChild(s);
	
	showMap(0);
}

void WorldMapScene::showMap(int index)
{
	curIndex = index;
	worldLayer->removeChildByTag(0);
	Sprite* worldbg = Sprite::create("worldmap/" + worldData[index].bg);
	//worldbg->setOpacity(150);
	worldLayer->addChild(worldbg, 0, 0);
	worldname->setString(worldData[index].name);

	lp_layer->removeAllChildren();
	int size = worldData[index].levelpoint.size();
	for (int i = 0; i < size; i++)
	{
		Button* lp = Button::create("star00.png","","",ui::Widget::TextureResType::PLIST);
		lp->setPosition(Point(worldData[index].levelpoint[i].x, worldData[index].levelpoint[i].y));
		lp->setTag(i);
		lp->addClickEventListener(CC_CALLBACK_1(WorldMapScene::event_lp_click, this));

		lp_layer->addChild(lp);
	}
}

void WorldMapScene::event_lp_click(cocos2d::Ref* sender)
{
	Button* button = static_cast<Button*>(sender);
	LoadingScene* loading = LoadingScene::create();
	ValueMap map;
	map["world"] = 1 + curIndex;
	map["level"] = 1 + button->getTag();
	loading->setData(map);


	std::queue<LoadingScene::LoadingCallback> list;
	list.push([](){
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		textureList.push_back("texture/UI/TowerSelectLayer.plist");
		textureList.push_back("texture/UI/TowerInfoLayer.plist");
		textureList.push_back("texture/UI/GameMapInfoLayer.plist");
		textureList.push_back("texture/icon/Icon_000.plist");
		TextureManager::getInstance()->LoadResource(textureList);
	});
	list.push([](){ TowerCardManager::getInstance()->LoadResource();});
	list.push([](){ SpellCardManager::getInstance()->LoadResource(); });
	list.push([](){ WeaponManager::getInstance()->LoadResource(); });
	loading->setLambdaLoadList(list);	



	loading->bindFinishFunction([=](){
		PrepareScene* scene = PrepareScene::create();
		ValueMap map = loading->getData();
		if (scene->initData(map["world"].asInt(), map["level"].asInt()))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)scene));
		}
	});

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)loading));
}

void WorldMapScene::event_world_click(cocos2d::Ref* sender)
{
	Button* button = static_cast<Button*>(sender);
	int index = button->getTag();

	if (index != curIndex)
	{
		for (auto item : listview->getItems())
		{
			Button* bt = static_cast<Button*>(item);
			bt->removeAllChildren();
		}

		Sprite* s = Sprite::createWithSpriteFrameName("worldbutton_select.png");
		Size size = button->getContentSize();
		s->setPosition(Point(size.width / 2, size.height / 2));
		button->addChild(s);

		showMap(index);
	}
}



void WorldMapScene::event_btReturn_click()
{
	LoadingScene* loading = LoadingScene::create();

	loading->bindFinishFunction([=](){
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)TitleScene::createScene()));
	});

	loading->replaceScene(loading);

}
