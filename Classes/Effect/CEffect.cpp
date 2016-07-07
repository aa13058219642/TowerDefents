#include "CEffect.h"

CEffect::CEffect()
{
	lifetime = 0;
}


CEffect::~CEffect()
{

}

void CEffect::setParent(GameObject* parent)
{
	this->m_parent = parent;
}

void CEffect::setTarget(GameObject* target)
{
	this->m_target = target;
}

void CEffect::updateLifeTime(float dt)
{
	lifetime -= dt;
	//if (lifetime <= 0){
	//	Uninstall();
	//}
}