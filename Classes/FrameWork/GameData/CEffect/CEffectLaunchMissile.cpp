#include "CEffectLaunchMissile.h"
#include "BulletFactory.h"
using namespace cocosgalaxy;


CEffectLaunchMissile::CEffectLaunchMissile(int BulletID)
{
	this->BulletID = BulletID;
}


CEffectLaunchMissile::~CEffectLaunchMissile()
{

}

void CEffectLaunchMissile::execute()
{
	//Bullet* bullet = BulletFactory::getInstance()->CreateBullet(BulletID, getParent()->getPos(), getTarget());
	
	CUnit* unit = UnitManager::getInstance()->CreateUnit(BulletID);
	//unit->setWeapon(getTarget()->getWeapon());
	unit->setTarget(getTarget()->ID);
	unit->setPos(getParent()->getPos());
	UnitManager::getInstance()->addUnit(unit);

	this->setState(ECEffectState::ECEffectState_Death);
}



CEffect* CEffectLaunchMissile::clone()
{
	CEffectLaunchMissile* effect = new CEffectLaunchMissile(BulletID);
	return effect;
}













