#pragma once
#include "stdfax.h"
#include "GameObject.h"

class CEffect
{
public:
	CEffect();
	~CEffect();

	//virtual void Install();
	//virtual void Uninstall();
	virtual CEffect* clone()=0;
	virtual void execute()=0;
	virtual void updateLifeTime(float dt);
	void setParent(GameObject* parent);
	void setTarget(GameObject* target);

	string id;
	float lifetime;
protected:
	GameObject* m_parent;
	GameObject* m_target;

};

