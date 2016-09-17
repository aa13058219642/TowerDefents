#pragma once
#include "stdfax.h"
#include "Unit.h"

class Bullet : public Unit
{
public:
	Bullet();
	Bullet(CWeapon* weapon, int parentID, int targetID, Point pos);

	~Bullet();


	/*绘制轮廓*/
	virtual void drawMyOutLine(DrawNode* drawNode);
	virtual void update(float dt);

	void setParent(int patentID);
	Unit* getParent();

	void setTarget(int targetID);
	Unit* getTarget();



	virtual void onMissTarget(Unit* target);

	virtual void setIsTrackTarget(bool IsTrackTarget);			//是否跟踪目标
	virtual void setIsFaceToTargetPos(bool IsFaceToTargetPos);	//方向是否指向目标
	virtual void setOnHitEffect(CEffect* effect);				//设置命中后的效果

	virtual Bullet* clone();//浅拷贝

protected:
	Point m_targetPos;
	int m_parentID;
	int m_targetID;
	CEffect* m_hitEffect;


	bool isTrackTarget;
	bool isFaceToTargetPos;

	virtual void onTargetDead();
	virtual void onMove(float dt);
	virtual void onHitTarget();
	virtual void onDead();
};

