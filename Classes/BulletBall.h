#pragma once
#include "Bullet.h"


class BulletBall :public Bullet
{
public:
	BulletBall();
	~BulletBall();

	static BulletBall* create();
	bool init();

	virtual void update(float dt);

private:
	virtual void onMove(float dt);
};

