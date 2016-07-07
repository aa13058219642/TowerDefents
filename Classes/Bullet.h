#pragma once
#include "stdfax.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	static Bullet* create();
	bool init();

	/*»æÖÆÂÖÀª*/
	virtual void drawMyOutLine(DrawNode* drawNode);

	virtual void update(float dt);

	virtual void onMissTarget(GameObject* target);
	virtual void setAbility(Ability ability);
	virtual void setTarget(GameObject* target);

	virtual GameObjectType getObjectType();
protected:
	Point targetPos;
	GameObject* target;

	virtual void onTargetDead();
	virtual void onMove(float dt);
	virtual void onHitTarget();

};

