#pragma once
#include "Bullet.h"


class BulletMissile :public Bullet
{
public:
	BulletMissile();
	~BulletMissile();

	static BulletMissile* create();
	bool init();

	virtual void update(float dt);

private:
	virtual void onMove(float dt);
};

