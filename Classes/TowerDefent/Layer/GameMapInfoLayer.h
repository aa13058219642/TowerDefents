#pragma once
#include "stdfax.h"
#include "Message\MessageListener.h"

class GameMapInfoLayer : public Layer, MessageListener
{
public:
	GameMapInfoLayer();
	~GameMapInfoLayer();

	static GameMapInfoLayer* create();
	virtual bool init();
	virtual void update(float dt);
	virtual void receive(const Message* message);


private:

	//TopLeft1
	Layer* layer_TopLeft1;
	Sprite* bg_TopLeft1;
	Sprite* bt_WaveIcon;
	Label* lab_Life;
	Label* lab_Money;
	Label* lab_Wave;

	//TopLeft2
	Layer* layer_TopLeft2;
	Sprite* bg_TopLeft2;
	Rect bt_NextWave;
	Label* lab_NaxtWaveInfo;

	//TopRight
	Layer*  layer_TopRight;
	Rect bt_CardInfo;
	Rect bt_Option;
	Sprite* bg_TopRight;

	//BottomLeft
	Layer*  layer_BottomLeft;
	Sprite* bg_BottomLeft;
	Sprite* bt_DoubleSpeed;
	Sprite* bt_Pause;

	void receiveMsg(Ref* pData);


	void initSprite();
	void initListener();




};
