#include "BulletFactory.h"
#include "EffectManager.h"
#include "UnitManager.h"
#include "TDUnitCreator.h"
using namespace cocosgalaxy;

BulletFactory* BulletFactory::p_myinstance = NULL;

BulletFactory::BulletFactory()
{

}

BulletFactory* BulletFactory::getInstance()
{
	if (p_myinstance == NULL)
	{
		p_myinstance = new BulletFactory();
		p_myinstance->LoadBulletList();
	}
	return p_myinstance;
}

int BulletFactory::LoadBulletList()
{
	Bullet* bullet;
	BulletType type;

	//从文件读取所有弹头
	//ID=0 ///////////////////////////////////////////////////////////////
	type = EBulletType::Ball;

	bullet = new Bullet();
	bullet->name = "Bullet001";
	bullet->setType(EUnitType::Bullet);
	bullet->setIsTrackTarget(false);
	bullet->setIsFaceToTargetPos(false);

	bullet->Radius = 8;
	bullet->Speed = 800;

	bullet->setOnHitEffect(EffectManager::getInstance()->createCEffect("missileDamage"));
	bullet->setActorName("b001");

	//bullet->retain();
	bulletlist[0] = bullet;


	//ID=1 ///////////////////////////////////////////////////////////////
	type = EBulletType::Missile;
	bullet = new Bullet();
	bullet->name = "Bullet002";
	bullet->setType(EUnitType::Bullet);
	bullet->setIsTrackTarget(true);
	bullet->setIsFaceToTargetPos(true);

	bullet->Radius = 8;
	bullet->Speed = 500;

	bullet->setOnHitEffect(EffectManager::getInstance()->createCEffect("missileDamage"));
	bullet->setActorName("b002");

	//bullet->retain();
	bulletlist[1] = bullet;

	//ID=2 ///////////////////////////////////////////////////////////////
	type = EBulletType::Missile;
	bullet = new Bullet();
	bullet->name = "Bullet003";
	bullet->setType(EUnitType::Bullet);
	bullet->setIsTrackTarget(false);
	bullet->setIsFaceToTargetPos(true);

	bullet->Radius = 8;
	bullet->Speed = 100;

	bullet->setOnHitEffect(EffectManager::getInstance()->createCEffect("MissileBoom"));
	bullet->setActorName("b003");

	//bullet->retain();
	bulletlist[2] = bullet;

	return 0;
}



Bullet* BulletFactory::CreateBullet(int BulletID, Point pos, CUnit* target)
{
	Bullet* bullet = bulletlist[BulletID]->clone();
	UnitManager::getInstance()->addUnit(bullet);
	
	bullet->setPos(pos);
	bullet->setTarget(target->ID);

	return bullet;
}

Bullet* BulletFactory::CreateBullet(int BulletID)
{
	return bulletlist[BulletID]->clone();
}

Bullet* BulletFactory::CreateBullet(string bulletName)
{
	Bullet* bullet = nullptr;
	for (auto& b : bulletlist)
	{
		if (b.second->name == bulletName)
		{
			bullet = b.second->clone();
		}
	}

	CCASSERT(bullet != nullptr, "Unknow bullet name !");

	return bullet;
}







