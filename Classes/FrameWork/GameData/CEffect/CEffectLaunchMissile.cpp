#include "CEffectLaunchMissile.h"
#include "BulletFactory.h"
#include "UnitManager.h"

CEffectLaunchMissile::CEffectLaunchMissile(int BulletID)
{
	this->BulletID = BulletID;
}


CEffectLaunchMissile::~CEffectLaunchMissile()
{

}

void CEffectLaunchMissile::execute()
{
	Bullet* bullet = BulletFactory::getInstance()->CreateBullet(BulletID, getParent()->getPos(), getTarget());

	this->setState(ECEffectState::ECEffectState_Death);
}



CEffect* CEffectLaunchMissile::clone()
{
	CEffectLaunchMissile* effect = new CEffectLaunchMissile(BulletID);
	return effect;
}













