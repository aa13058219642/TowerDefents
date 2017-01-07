#include "GameMapInfoLayer.h"
#include "AnimateManager.h"

GameMapInfoLayer::GameMapInfoLayer(){}

GameMapInfoLayer::~GameMapInfoLayer(){}

GameMapInfoLayer* GameMapInfoLayer::create()
{
	GameMapInfoLayer* layer = new GameMapInfoLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(layer);
	}
	return layer;
}

bool GameMapInfoLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initSprite();
	this->initListener();

	return true;
}



void GameMapInfoLayer::initSprite()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float scale = 1 / Director::getInstance()->getContentScaleFactor();
	cocos2d::TTFConfig ttfconfig1("fonts/STENCIL.TTF", 30, GlyphCollection::DYNAMIC, nullptr, false, 0);
	cocos2d::TTFConfig ttfconfig2("fonts/SIMYOU.TTF", 30, GlyphCollection::DYNAMIC, nullptr, false, 2);


	//TopLeft1	##################################################################
	bg_TopLeft1 = Sprite::createWithSpriteFrameName("GameMapInfoLayer_000.png");
	bg_TopLeft1->setAnchorPoint(Point(0, 0));

	bt_WaveIcon = Sprite::createWithSpriteFrameName("WaveIcon_000.png");
	bt_WaveIcon->setPosition(Point(72,32)*scale);
	AnimateManager::getInstance()->playAnimate("waveIcon", bt_WaveIcon);

	//lab_Life = Label::createWithTTF("20", "fonts/SIMYOU.TTF", 30, Size::ZERO);
	lab_Life = Label::createWithTTF(ttfconfig1, "20");
	lab_Life->setAnchorPoint(Point(0, 0.5));
	lab_Life->setPosition(Point(77, 125)*scale);

	lab_Money = Label::createWithTTF(ttfconfig1, "9999");
	lab_Money->setAnchorPoint(Point(0, 0.5));
	lab_Money->setPosition(Point(185, 125)*scale);

	lab_Wave = Label::createWithTTF(ttfconfig1, "0/20");
	lab_Wave->setAnchorPoint(Point(0, 0.5));
	lab_Wave->setPosition(Point(185, 60)*scale);

	layer_TopLeft1 = Layer::create();
	layer_TopLeft1->setAnchorPoint(Point(0, 0));
	layer_TopLeft1->setPosition(Point(0, visibleSize.height*scale - bg_TopLeft1->getContentSize().height));
	layer_TopLeft1->addChild(bg_TopLeft1);
	layer_TopLeft1->addChild(bt_WaveIcon);
	layer_TopLeft1->addChild(lab_Life);
	layer_TopLeft1->addChild(lab_Money);
	layer_TopLeft1->addChild(lab_Wave);
	this->addChild(layer_TopLeft1, 2);

	//TopLeft2	##################################################################
	Sprite* bg_TopLeft2 = Sprite::createWithSpriteFrameName("GameMapInfoLayer_001.png");
	bg_TopLeft2->setAnchorPoint(Point(0, 0));

	Label* lab_NaxtWaveInfo = Label::createWithTTF(ttfconfig2, "Next Wave\n怪物000   x1", TextHAlignment::LEFT, 280);
	//LabelTTF*  lab_NaxtWaveInfo = LabelTTF::create("", "fonts/SIMYOU.TTF", 30);
	//Label* lab_NaxtWaveInfo = Label::createWithTTF(ttfconfig2, "");
	lab_NaxtWaveInfo->setAnchorPoint(Point(0, 0));
	//lab_NaxtWaveInfo->setLineBreakWithoutSpace(true);
	string str = "Next Wave\n怪物00 x1\n怪物01 x11\n怪物02 x30\n怪物03 x11\n";
	int x = 0;
	int v = 0;
	int u = 0;
	while (u != string::npos)
	{
		v = str.find("\n", u + 1);
		if (v != -1)
			u = v; 
		else
			break;
		x++;
	}
	if (u == str.length() - 1)
		x--;

	lab_NaxtWaveInfo->setString(str);


	//lab_NaxtWaveInfo->setLineHeight(30);
	lab_NaxtWaveInfo->setPosition(Point(8, 80)*scale);

	Rect bt_NextWave;

	Layer* layer_TopLeft2 = Layer::create(); 
	layer_TopLeft2->setAnchorPoint(Point(0, 0));
	layer_TopLeft2->setPosition(Point(0, visibleSize.height*scale - bg_TopLeft2->getContentSize().height));
	layer_TopLeft2->addChild(bg_TopLeft2);
	layer_TopLeft2->addChild(lab_NaxtWaveInfo);
	this->addChild(layer_TopLeft2, 1);

	//BottomLeft	##################################################################
	bg_BottomLeft = Sprite::createWithSpriteFrameName("GameMapInfoLayer_002.png");
	bg_BottomLeft->setAnchorPoint(Point(0, 0));

	Sprite* bt_DoubleSpeed = Sprite::createWithSpriteFrameName("DoubleSpeed_0.png");
	bt_DoubleSpeed->setPosition(Point(64, 35)*scale);

	Sprite* bt_Pause = Sprite::createWithSpriteFrameName("Pause_0.png");
	bt_Pause->setPosition(Point(136, 32)*scale);

	layer_BottomLeft = Layer::create();
	layer_BottomLeft->setAnchorPoint(Point(0, 0));
	layer_BottomLeft->addChild(bg_BottomLeft);
	layer_BottomLeft->addChild(bt_DoubleSpeed);
	layer_BottomLeft->addChild(bt_Pause);
	this->addChild(layer_BottomLeft);




	//TopRight	##################################################################
	Sprite* bg_TopRight = Sprite::createWithSpriteFrameName("GameMapInfoLayer_003.png");
	bg_TopRight->setAnchorPoint(Point(0, 0));

	bt_CardInfo = Rect(1120, 832, 80, 80);
	bt_Option = Rect(1200, 832, 80, 80);

	layer_TopRight = Layer::create();
	layer_TopRight->setAnchorPoint(Point(0, 0));
	Size size = bg_TopRight->getContentSize();
	layer_TopRight->setPosition(Point(visibleSize.width*scale - size.width, visibleSize.height*scale - size.height));
	layer_TopRight->addChild(bg_TopRight);
	this->addChild(layer_TopRight);


}

void GameMapInfoLayer::initListener()
{


}




void GameMapInfoLayer::update(float dt){

}

