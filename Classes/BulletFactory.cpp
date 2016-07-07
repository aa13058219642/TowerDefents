#include "BulletFactory.h"
#include "BulletBall.h"
#include "BulletMissile.h"
BulletFactory* BulletFactory::p_myinstance = NULL;

BulletFactory::BulletFactory()
{

}

BulletFactory* BulletFactory::getInstance()
{
	if (p_myinstance == NULL)
	{
		p_myinstance = new BulletFactory();
	}
	return p_myinstance;
}



Bullet* BulletFactory::CreateBullet(int BulletID, Point pos, GameObject* target)
{
	Bullet* bullet;

	BulletType type = getBulletType(BulletID);
	switch (type)		
	{
	default:
	case Ball:
		bullet = BulletBall::create();
		break;
	case Missile:
		bullet = BulletMissile::create();
		break;
	}
	bullet->setPos(pos);
	bullet->setPosition(pos);
	bullet->setTarget(target);
	bullet->setAbility(getAbility(BulletID));
	bullet->bindSprite(getSprite(BulletID));

	return bullet;
}


BulletType BulletFactory::getBulletType(int BulletID)
{
	switch (BulletID)
	{
	default:
	case 0:return BulletType::Ball; break;
	case 1:return BulletType::Missile; break;
	}

	
}


Sprite* BulletFactory::getSprite(int BulletID)
{
	Sprite* sprite;
	switch (BulletID)
	{
	default:
	case 0:sprite = Sprite::create("bullet/bullet_0.png"); break;
	case 1:sprite = Sprite::create("bullet/bullet_1.png"); break;
	}
	//std::string file = StringUtils::format("bullet/bullet_1.png", 2);
	sprite->setPosition(0, 0);
	////sprite->runAction(ActionManager::)



	return sprite;
}

Ability BulletFactory::getAbility(int BulletID)
{
	Ability ability;
	ability.WAtk = 10;
	ability.Radius = 8;
	ability.Speed = 500;
	return ability;
}







