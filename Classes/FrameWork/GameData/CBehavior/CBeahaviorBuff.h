#pragma once
#include "stdfax.h"
#include "CBehavior.h"
#include "Modification.h"




class CBeahaviorBuff : public CBehavior
{
public:
	CBeahaviorBuff();
	~CBeahaviorBuff();

	virtual CBehavior* clone();
	virtual bool meetRequirement();
	virtual void Install(Unit* parent);
	virtual void Uninstall(Unit* parent);
	virtual void update(float dt);

	list<Modification> m_modList;	//修正
	//Verfier m_verfier;			//验证器
	bool isTimeLimitBuff;			//限时BUFF
	float m_lifetime;				//作用时长
	float m_cycle;					//周期
	Name m_cycleEffect;				//周期效果
	int m_cycleCount;				//周期数
	//DamageResponse m_damageResponse;//伤害响应
private:




};

