#pragma once
#include "stdfax.h"


struct ActorData{
	std::string defaultanimate = "";
	map<Name, Name> maps;
};


class Actor
{
public:
	int ID;

	Actor();
	Actor(int id, ActorData data, Layer* parent);
	~Actor();

	Actor* clone();
	void bindSprite(Layer* parent);

	void setPos(Point pos);
	void setRotation(float rotation);
	void setDefaultAnimate(const Name& defaultAnimate);
	void setAnimateList(map<Name, Name> animateList);

	/*设置是否显示血条，默认不显示*/
	void setShowHpBar(bool isShow, Point pos = Point::ZERO, Size size = Size::ZERO);
	/*设置血条百分比 [0,1]*/
	void setHpBarProgress(float progress);
	/*设置是否显示占位格子*/
	void setShowUnitPos(bool isShow);

	void playDefaultAnimate();
	void playAction(const Name& actionName, float playtime = 0, Color3B color = Color3B::WHITE);
	void playEffect(const Name& animateName, float playtime = 0, Color3B color = Color3B::WHITE, Point offset = Point::ZERO, int localZOrder = 1);

	void remove();

	enum Face: int{FACE_TO_LEFT,FACE_TO_RIGHT};
	void changeFace(Face face);

	bool IsExistAnimate(const Name& animateName);
private:
	Layer* m_layer;
	Point m_pos;
	Layer* m_parent;

	Face m_face;
	Sprite* m_sprite;
	cocos2d::ui::Scale9Sprite* m_hpBar;
	Sprite* m_unitPos;

	Name m_defaultAnimate;
	map<Name, Name> m_animateList;


};

