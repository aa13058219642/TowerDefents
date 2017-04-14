#include "CEffectLaunchMissile.h"
#include "UnitManager.h"
using namespace cocosgalaxy;

CEffectLaunchMissile::CEffectLaunchMissile()
{
	this->className = "";
	this->typeName = "";
}

CEffectLaunchMissile::CEffectLaunchMissile(string className, string typeName)
{
	this->className = className;
	this->typeName = typeName;
}


CEffectLaunchMissile::~CEffectLaunchMissile()
{

}

void CEffectLaunchMissile::execute()
{
	CUnit* unit = UnitManager::getInstance()->CreateUnit(className, typeName);
	vector<int> targets;
	targets.push_back(m_targetID);
	unit->setTarget(targets);
	unit->setPos(getParent()->getPos());
	UnitManager::getInstance()->addUnit(unit);

	this->setState(ECEffectState::ECEffectState_Death);
}



CEffect* CEffectLaunchMissile::clone()
{
	CEffectLaunchMissile* effect = new CEffectLaunchMissile(className, typeName);
	return effect;
}













