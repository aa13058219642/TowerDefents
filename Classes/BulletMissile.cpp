#include "BulletMissile.h"
#include "GameObjectLayer.h"

BulletMissile::BulletMissile()
{

}


BulletMissile::~BulletMissile()
{

}

BulletMissile* BulletMissile::create()
{
	BulletMissile* bullet = new BulletMissile();
	if (bullet && bullet->init())
	{
		bullet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bullet);
	}
	return bullet;
}

bool BulletMissile::init()
{
	bool flag = false;

	do{
		if (!Bullet::init())
			break;


		flag = true;
	} while (0);

	return flag;
}

void BulletMissile::update(float dt)
{
	onMove(dt);
}


void BulletMissile::onMove(float dt)
{
	if (target != NULL)
		targetPos = target->getPos();

	float dis, move, a;
	dis = m_pos.distance(targetPos);
	if (dis > 0){
		move = cur_ability.Speed*dt;
		a = move / dis;
		if (a < 1){
			m_pos = a*(targetPos - m_pos) + m_pos;
			setPosition(m_pos);

			float angel = -(targetPos-m_pos).getAngle();
			this->getSprite()->setRotation(angel*180/3.14);

			return;
		}
	}

	onHitTarget();

}













