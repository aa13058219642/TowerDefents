#include "BulletBall.h"
#include "GameObjectLayer.h"

BulletBall::BulletBall()
{

}


BulletBall::~BulletBall()
{

}

BulletBall* BulletBall::create()
{
	BulletBall* bulletball = new BulletBall();
	if (bulletball && bulletball->init())
	{
		bulletball->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bulletball);
	}
	return bulletball;
}

bool BulletBall::init()
{
	bool flag = false;

	do{
		if (!Bullet::init())
			break;


		flag = true;
	} while (0);

	return flag;
}

void BulletBall::update(float dt)
{
	onMove(dt);
}


void BulletBall::onMove(float dt)
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
			return;
		}
	}

	onHitTarget();

}













