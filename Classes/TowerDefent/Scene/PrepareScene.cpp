#include "PrepareScene.h"
#include "LoadingScene.h"
#include "WorldMapScene.h"
#include "UserData.h"
#include "TowerDefentShare.h"
#include "BattleScene.h"


#include "TextureManager.h"
#include "AnimateManager.h"
#include "UnitManager.h"
#include "ActorManager.h"
#include "WeaponManager.h"
#include "EffectManager.h"
#include "SkillManager.h"
#include "BehaviorManager.h"
#include "SpellCardManager.h"
#include "TowerCardManager.h"
#include "TDUnitCreator.h"
#include "BulletManager.h"
#include "Player.h"
#include "MonsterManager.h"

using namespace cocos2d;
using namespace cocos2d::ui;

bool CardGridItem::init()
{
	if (!GridItem::init())
	{
		return false;
	}

	id = -1;
	tcard = nullptr;
	scard = nullptr;
	this->setContentSize(Size(64, 64));
	isChoose = false;
	return true;
}

void CardGridItem::onTouchEnded(Touch* touch, Event* event)
{
	Message msg;
	msg.keyword = "card_info";
	ValueMap map;
	map["id"] = this->id;
	map["isChoose"] = this->isChoose;
	msg.valueMap = map;
	msg.post(Message_PrepareScene);
}

void CardGridItem::setIcon(string iconname)
{
	this->iconName = iconname;

	Sprite* s = Sprite::create();
	s->setSpriteFrame(iconname);
	s->setPosition(this->getContentSize() / 2);
	this->addChild(s);
}


CardGridItem* CardGridItem::clone()
{
	CardGridItem* item = CardGridItem::create();
	item->type = this->type;
	item->tcard = this->tcard;
	item->scard = this->scard;
	item->isChoose = this->isChoose;
	item->setIcon(this->iconName);
	return item;
}


//////////////////////////////////////////////////////////////////////////////////////


PrepareScene::PrepareScene(){}

PrepareScene::~PrepareScene(){}


bool PrepareScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	initUI();
	initListener();
	return true;
}

void PrepareScene::initUI()
{
	Widget* widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("PrepareLayer.ExportJson");
	this->addChild(widget);

	//设置拉伸BG
	Sprite* bg = Sprite::create("ui_bg.png");
	bg->setAnchorPoint(Point(0, 0));
	bg->setColor(Color3B(0, 204, 255));
	Size size = Director::getInstance()->getVisibleSize();
	float scale = MAX(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
	bg->setScale(scale);
	widget->addChild(bg, -1);

	//载入控件 
	Layout* panel = static_cast<Layout*>(widget->getChildByName("panel"));
	panel->setLocalZOrder(1);

	cb_tabbt_card = static_cast<CheckBox*>(panel->getChildByName("cb_tabbt_card"));
	cb_tabbt_map = static_cast<CheckBox*>(panel->getChildByName("cb_tabbt_map"));
	bt_go = static_cast<Button*>(panel->getChildByName("bt_go"));
	bt_return = static_cast<Button*>(panel->getChildByName("bt_return"));
	bt_addmoney = static_cast<Button*>(panel->getChildByName("bt_addmoney"));
	label_money = static_cast<Text*>(panel->getChildByName("label_money"));
	label_cost = static_cast<Text*>(panel->getChildByName("label_cost"));

	panel_selectionCard = static_cast<Layout*>(panel->getChildByName("panel_selectionCard"));
	panel_selectionCard->setLocalZOrder(2);
	image_dialogBG = static_cast<ImageView*>(panel->getChildByName("image_dialogBG"));
	title0 = static_cast<Text*>(panel->getChildByName("title0"));

	panel_card_left = static_cast<Layout*>(panel->getChildByName("panel_card_left"));
	panel_card_left->setLocalZOrder(2);
	title1 = static_cast<Text*>(panel_card_left->getChildByName("title1"));
	panel_gridview1 = static_cast<Layout*>(panel_card_left->getChildByName("panel_gridview1"));

	panel_card_right = static_cast<Layout*>(panel->getChildByName("panel_card_right"));
	panel_card_right->setLocalZOrder(2);
	title2 = static_cast<Text*>(panel_card_right->getChildByName("title2"));
	cardinfo = static_cast<Text*>(panel_card_right->getChildByName("cardinfo"));
	bt_choose = static_cast<Button*>(panel_card_right->getChildByName("bt_choose"));
	image_card = static_cast<ImageView*>(panel_card_right->getChildByName("card"));
	image_card->setVisible(false);

	panel_map_left = static_cast<Layout*>(panel->getChildByName("panel_map_left"));
	panel_map_left->setLocalZOrder(2);
	title3 = static_cast<Text*>(panel_map_left->getChildByName("title3"));
	image_map = static_cast<ImageView*>(panel_map_left->getChildByName("image_map"));

	panel_map_right = static_cast<Layout*>(panel->getChildByName("panel_map_right"));
	panel_map_left->setLocalZOrder(2);
	title4 = static_cast<Text*>(panel_map_right->getChildByName("title4"));
	panel_gridview2 = static_cast<Layout*>(panel_map_right->getChildByName("panel_gridview4"));

	//载入gridview
	gridview1 = GridPageView::create(Size(340,271), Size(64, 64), GridView::Direction::VERTICAL);
	gridview1->setSpacing(5, 5);
	gridview1->setPosition(Size(200,160));
	//gridview1->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	panel_card_left->addChild(gridview1);

	gridview2 = GridPageView::create(Size(560,134), Size(64, 64), GridView::Direction::VERTICAL);
	gridview2->setSpacing(5, 5);
	gridview2->setPosition(Size(280, 67));
	panel_selectionCard->addChild(gridview2);

	gridItem_selected1 = Sprite::createWithSpriteFrameName("griditem_selected.png");
	gridItem_selected1->setVisible(false);
	gridItem_selected1->runAction(RepeatForever::create(RotateBy::create(5.0f, 60)));
	panel_card_left->addChild(gridItem_selected1, -1);

	gridItem_selected2 = Sprite::createWithSpriteFrameName("griditem_selected.png");
	gridItem_selected2->setVisible(false);
	gridItem_selected2->runAction(RepeatForever::create(RotateBy::create(5.0f, 60)));
	panel_selectionCard->addChild(gridItem_selected2, -1);

	//隐藏部分UI
	image_dialogBG->loadTexture("dialog_bg.png");

	panel_card_left->setVisible(false);
	panel_card_right->setVisible(false);
	panel_map_left->setVisible(true);
	panel_map_right->setVisible(true);
	cb_tabbt_card->setSelected(false);
	cb_tabbt_map->setSelected(true);

	curItem = nullptr;

}

bool PrepareScene::initData(int wrold, int level)
{
	m_wrold = wrold;
	m_level = level;
	this->initPlayerData();
	return this->initMapData(wrold, level);
}

void PrepareScene::initPlayerData()
{
	UserData* userdata = UserData::getInstance();

	TowerCardManager* tmgr = TowerCardManager::getInstance();
	SpellCardManager* smgr = SpellCardManager::getInstance();

	for (int i = 0; i < 8; i++)
	{
		const TowerCard* tcard = tmgr->getTowerCard(i);
		CardGridItem* item = CardGridItem::create();
		item->type = CardGridItem::CardGridItemType::tower;
		item->tcard = tcard;
		item->setContentSize(Size(64, 64));
		item->setIcon(tcard->Icon);

		itemlist.pushBack(item);
		gridview1->addItem(item);
	}
	for (int i = 0; i < 8; i++)
	{
		const SpellCard* scard = smgr->getSpellCard(i);
		CardGridItem* item = CardGridItem::create();
		item->type = CardGridItem::CardGridItemType::spell;
		item->scard = scard;
		item->setContentSize(Size(64, 64));
		item->setIcon(scard->Icon);

		itemlist.pushBack(item);
		gridview1->addItem(item);
	}


}

bool PrepareScene::initMapData(int wrold, int level)
{
	bool flag = true;

	do{
		string levelname = StringUtils::format("%d-%d", wrold, level);

		//1.打开文件
		FileUtils* fin = FileUtils::getInstance();
		Data data = fin->getDataFromFile("data/LevelData.json");
		if (data.isNull())
		{
			CCASSERT(false, "[LevelData.json] Lost!");
			flag = false;
			break;
		}

		//2.载入json
		string str = string((char*)data.getBytes(), data.getSize());
		rapidjson::Document root;
		root.Parse<0>(str.c_str());
		if(!(root.IsObject() && root.HasMember("leveldata") && root["leveldata"].IsObject()))
		{
			CCASSERT(false, "illegal [LevelData.json]");
			flag = false;
			break;
		}

		//3.读取json数据
		if (root["leveldata"].HasMember(levelname.c_str()) && root["leveldata"][levelname.c_str()].IsObject())
		{
			JsonNode jNode = root["leveldata"][levelname.c_str()];

			m_title = jNode["title"].GetString();
			string str1 = StringUtils::format("%s %s", levelname.c_str(), m_title.c_str());
			title0->setString(str1);

			str1 = StringUtils::format("minimap/%s", string(jNode["minimap"].GetString()).c_str());
			image_map->loadTexture(str1);

			int money = jNode["beginMoney"].GetInt();
			label_money->setString(StringUtils::format("%d", money));
			BaseMoney = money;
			AddMoney = 0;

			money = jNode["awardMoney"].GetInt();
			AwardMoney = money;
		}
		else
		{
			CCASSERT(false, StringUtils::format("ERROR %s NOT found", levelname.c_str()).c_str());
			flag = false;
			break;
		}
	} while (0);

	return flag;
}

void PrepareScene::initListener()
{
	//设置事件
	bt_go->addClickEventListener(CC_CALLBACK_0(PrepareScene::event_btGO_click, this));
	bt_return->addClickEventListener(CC_CALLBACK_0(PrepareScene::event_btReturn_click, this));
	bt_choose->addClickEventListener(CC_CALLBACK_0(PrepareScene::event_btChoose_click, this));

	cb_tabbt_map->addClickEventListener([=](Ref* pSender){
		panel_card_left->setVisible(false);
		panel_card_right->setVisible(false);
		panel_map_left->setVisible(true);
		panel_map_right->setVisible(true);
		cb_tabbt_card->setSelected(false);
		cb_tabbt_map->setSelected(true);
	});

	cb_tabbt_card->addClickEventListener([=](Ref* pSender){
		panel_card_left->setVisible(true);
		panel_card_right->setVisible(true);
		panel_map_left->setVisible(false);
		panel_map_right->setVisible(false);
		cb_tabbt_card->setSelected(true);
		cb_tabbt_map->setSelected(false);
	});

	msgSubscribe(Message_PrepareScene);
}

void PrepareScene::receive(const Message* message)
{
	if (message->keyword == "card_info")
	{
		ValueMap map = message->valueMap;
		int id = map["id"].asInt();
		bool choose = map["isChoose"].asBool();

		if (choose)
		{
			curItem = (CardGridItem*)gridview2->getItem(id);
			bt_choose->loadTextureNormal("bt_rect_red.png", TextureResType::PLIST);
			bt_choose->setTitleText("Remove");

			gridItem_selected1->setVisible(false);
			gridItem_selected2->setVisible(true);
			gridItem_selected2->setPosition(
				gridview2->getPosition() - gridview2->getContentSize() / 2 +
				curItem->getPosition() + curItem->getContentSize() / 2);
		}
		else
		{
			curItem = (CardGridItem*)gridview1->getItem(id);
			bt_choose->loadTextureNormal("bt_rect_green.png", TextureResType::PLIST);
			bt_choose->setColor(Color3B::WHITE);
			bt_choose->setTitleText("Add");

			gridItem_selected1->setVisible(true);
			gridItem_selected2->setVisible(false);
			gridItem_selected1->setPosition(
				gridview1->getPosition() - gridview1->getContentSize() / 2 +
				curItem->getPosition() + curItem->getContentSize() / 2);
		}

		if (curItem->type == CardGridItem::CardGridItemType::tower)
		{
			string str = StringUtils::format("card/card_%03d.png", curItem->tcard->ID);
			image_card->loadTexture(str);
			image_card->setScale(0.25f);
			image_card->setVisible(true);

			title2->setString(curItem->tcard->uiName);

			CWeapon* weapon = WeaponManager::getInstance()->getWeapon(curItem->tcard->weaponName[0]);
			float scale = 1 / Director::getInstance()->getContentScaleFactor();
			str = StringUtils::format("Atk: %.0f-%.0f\nCD: %.3fs\nRange: %.0f/%.0f\nCritical: %.0f%%/%.0f%%\nTarget: %d",
				weapon->Damage.Min.getValue(), weapon->Damage.Max.getValue(),
				weapon->ColdDown.Max.getValue(),
				weapon->Range.getValue() / scale, weapon->BoomRange.getValue() / scale,
				weapon->criticalChance.getValue() * 100, weapon->criticalMultiplier.getValue() * 100,
				weapon->TargetCount.getValue()
				);

			cardinfo->setString(str);

			delete weapon;
		}
		else if (curItem->type == CardGridItem::CardGridItemType::spell)
		{
			//ActorManager::getInstance()->createActor(0, curItem->scard->);
			image_card->loadTexture(curItem->scard->Icon, Widget::TextureResType::PLIST);
			image_card->setScale(1);
			image_card->setVisible(true);
		
			cardinfo->setString("");
		}
		else
		{
			CCASSERT(false, "error griditem type !");
		}
	}
}

void PrepareScene::event_btGO_click()
{
	int size = gridview2->getItemCounnt();
	if (size <= 0)
	{
		return;
	}

	//init player
	std::vector<TowerCard> m_TowerCard;
	std::vector<SpellCard> m_SpellCard;
	for (int i = 0; i < size; i++)
	{
		CardGridItem* item = static_cast<CardGridItem*>(gridview2->getItem(i));
		if (item->type == CardGridItem::CardGridItemType::tower)
		{
			m_TowerCard.push_back(*item->tcard);
		}
		else if (item->type == CardGridItem::CardGridItemType::spell)
		{
			m_SpellCard.push_back(*item->scard);
		}
		else
		{
			CCASSERT(false, "error griditem type !");
		}
	}
	Player::getInstance()->setTowerCard(m_TowerCard);
	Player::getInstance()->setSpellCard(m_SpellCard);

	Player* player = Player::getInstance();
	player->reset();
	player->setMoney(BaseMoney + AddMoney);
	player->setLife(20);
	//

	LoadingScene* loading = LoadingScene::create();

	ValueMap map;
	map["wrold"] = m_wrold;
	map["level"] = m_level;
	map["title"] = m_title;
	map["awardMoney"] = AwardMoney;
	loading->setData(map);

	std::queue<LoadingScene::LoadingCallback> list;
	list.push([=](){ 		
		ValueMap map = loading->getData();

		LevelData leveldata;

		leveldata.world = map["wrold"].asInt();
		leveldata.level = map["level"].asInt();
		leveldata.title = map["title"].asString();
		leveldata.awardMoney = map["awardMoney"].asInt();

		GameMap::getInstance()->init(leveldata);
	});
	list.push([](){ UnitManager::getInstance()->init(new TDUnitCreator()); });
	list.push([](){ BehaviorManager::getInstance()->init(); });
	list.push([](){ EffectManager::getInstance()->init(); });
	list.push([](){
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		textureList.push_back("texture/UI/TowerSelectLayer.plist");
		textureList.push_back("texture/UI/TowerInfoLayer.plist");
		textureList.push_back("texture/UI/GameMapInfoLayer.plist");
		textureList.push_back("texture/effect/effect_000.plist");
		textureList.push_back("texture/icon/Icon_000.plist");
		textureList.push_back("texture/Tower/SpellTower.plist");
		TextureManager::getInstance()->LoadResource(textureList);
	});
	list.push([](){ AnimateManager::getInstance()->LoadResource(); });
	list.push([](){ ActorManager::getInstance()->LoadResource(); });
	list.push([](){ SkillManager::getInstance()->LoadResource(); });
	list.push([](){ BehaviorManager::getInstance()->LoadResource(); });
	list.push([](){ WeaponManager::getInstance()->LoadResource(); });
	list.push([](){ EffectManager::getInstance()->LoadResource(); });
	list.push([](){ BulletManager::getInstance()->LoadResource(); });
	list.push([](){ MonsterManager::getInstance()->LoadResource(); });

	loading->setLambdaLoadList(list);

	loading->bindFinishFunction([=](){
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)BattleScene::create()));
	});

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)loading));
}

void PrepareScene::event_btReturn_click()
{
	LoadingScene* loading = LoadingScene::create();

	loading->bindFinishFunction([=](){
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, (Scene*)WorldMapScene::createScene()));
	});

	loading->replaceScene(loading);
}

void PrepareScene::event_btChoose_click()
{
	if (curItem == nullptr)
	{
		return;
	}

	if (curItem->isChoose == false)
	{
		curItem->isChoose = true;
		gridview1->removeItem(curItem->id);
		gridview2->addItem(curItem);

		bt_choose->loadTextureNormal("bt_rect_red.png", TextureResType::PLIST);
		bt_choose->setTitleText("Remove");

		gridItem_selected1->setVisible(false);
		gridItem_selected2->setVisible(true);
		gridItem_selected2->setPosition(
			gridview2->getPosition() - gridview2->getContentSize() / 2 +
			curItem->getPosition() + curItem->getContentSize() / 2);
	}
	else
	{
		curItem->isChoose = false;
		gridview2->removeItem(curItem->id);
		gridview1->addItem(curItem);

		bt_choose->loadTextureNormal("bt_rect_green.png", TextureResType::PLIST);
		bt_choose->setTitleText("Add");

		gridItem_selected1->setVisible(true);
		gridItem_selected2->setVisible(false);
		gridItem_selected1->setPosition(
			gridview1->getPosition() - gridview1->getContentSize() / 2 +
			curItem->getPosition() + curItem->getContentSize() / 2);
	}
}
