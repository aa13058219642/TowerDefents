#include "Bullet.h"
#include "GameObjectLayer.h"

Bullet::Bullet()
{

}


Bullet::~Bullet()
{

}

Bullet* Bullet::create()
{
	Bullet* bulletbase = new Bullet();
	if (bulletbase && bulletbase->init())
	{
		bulletbase->autorelease();
	}
	else 
	{
		CC_SAFE_DELETE(bulletbase);
	}
	return bulletbase;
}

bool Bullet::init()
{
	bool flag = false;

	do{
		this->scheduleUpdate();
		flag = true;
	} while (0);

	return flag;
}

void Bullet::update(float dt)
{
	onMove(dt);
}


void Bullet::drawMyOutLine(DrawNode* drawNode)
{
	Point point[4];
	point[0] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[1] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[2] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y - cur_ability.Radius);
	point[3] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y - cur_ability.Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 1, 1, 0.3F), 1.0F, Color4F(1, 1, 1, 1));
}



void Bullet::setAbility(Ability ability)
{
	m_ability = ability;
	cur_ability = ability;
}

void Bullet::setTarget(GameObject* target)
{
	this->target = target;
	this->targetPos = target->getPos();
}

void Bullet::onMove(float dt){}

void Bullet::onHitTarget()
{
	//log("Bullet hit the target");
	if (target != NULL)
		target->onBeAttack(cur_ability.WAtk);

	this->onDead();
	GameObjectLayer* parent = (GameObjectLayer*)getParent();
	parent->bulletList.eraseObject(this);
	parent->removeChild(this);
}

void Bullet::onMissTarget(GameObject* target)
{
	if (this->target==target){
		this->target = NULL;
	}
}

void Bullet::onTargetDead()
{

}


