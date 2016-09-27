#pragma once
#include "stdfax.h"
#include "Tower.h"


class TowerInfoLayer : public Layer
{
public:
	TowerInfoLayer();
	~TowerInfoLayer();

	static TowerInfoLayer* create();
	virtual bool init();
	virtual void update(float dt);

	void show();
	void close();


private:
	Tower* m_parent;
	CWeapon* m_weapon;

	Point centerPos;
	Rect closeButton;

	Sprite* m_bg;
	Sprite* m_tower;
	Sprite* m_card;
	Sprite* m_switchButton;
	Label* m_label[8];		


	void initSprite();
	void initListener();

	void receiveMsg(Ref* pData);




};
