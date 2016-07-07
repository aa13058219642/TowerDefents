#include "CEffectLaunchMissile.h"
#include "BulletFactory.h"
#include "GameObjectLayer.h"

CEffectLaunchMissile::CEffectLaunchMissile(int BulletID)
{
	this->BulletID = BulletID;
}


CEffectLaunchMissile::~CEffectLaunchMissile()
{

}

void CEffectLaunchMissile::execute()
{
	//Bullet* bullet = BulletFactory::getInstance()->CreateBullet(BulletID, m_pos, target);
	Bullet* bullet = BulletFactory::getInstance()->CreateBullet(BulletID, m_parent->getPos(), m_target);
	//bullet->addToParent(this->m_parent->getParent());
	//this->m_parent->add
	this->m_parent->getPatentLayer()->addGameObject(bullet);

}



CEffect* CEffectLaunchMissile::clone()
{
	CEffectLaunchMissile* effect = new CEffectLaunchMissile(BulletID);
	return effect;
}

//void CEffectDamage::Install()
//{
//}
//
//
//
//void CEffectDamage::Uninstall()
//{
//
//}

//void CEffectSet::updateLifeTime(float dt)
//{
//	lifetime -= dt;
//	if (lifetime <= 0){
//		Uninstall();
//	}
//
//}













