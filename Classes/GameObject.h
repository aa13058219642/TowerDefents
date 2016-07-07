#pragma once
#include"stdfax.h"
#include"Ability.h"

enum GameObjectType
{
	GameObject_UnKnow = 0,
	GameObject_Tower,
	GameObject_Monster,
	GameObject_Bullet
};

class GameObjectLayer;

class GameObject : public Layer
{
public:
	GameObject();
	~GameObject();


	Ability m_ability;
	Ability cur_ability;
	CC_SYNTHESIZE(Point, m_pos, Pos);					//创建Pos的get set方法


	bool isClickMe(Point pos);	//判断坐标是否在RADIUS范围内
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();
	GameObjectLayer* getPatentLayer();

	/*绘制轮廓*/
	virtual void drawMyOutLine(DrawNode* drawNode);

	bool isDead();

	virtual void onBeAttack(int damage);
	virtual void onMissTarget(GameObject* target);

	virtual GameObjectType getObjectType() = 0;
protected:
	virtual void onBindSprite();
	virtual void onAttack();
	virtual void onMove();
	virtual void onHitTarget();
	virtual void onDead();

private:
	bool m_isDeath;				//是否死亡
	Sprite* m_sprite;			//精灵对象

};

