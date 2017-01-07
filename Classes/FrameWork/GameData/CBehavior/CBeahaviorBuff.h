#pragma once
#include "CBehavior.h"
#include "CModification.h"

namespace cocosgalaxy
{
	class CBeahaviorBuff : public CBehavior
	{
	public:
		CBeahaviorBuff();
		~CBeahaviorBuff();

		virtual CBehavior* clone();
		virtual bool meetRequirement();
		virtual void Install(CUnit* parent);
		virtual void Uninstall(CUnit* parent);
		virtual void update(float dt);

		list<CModification> m_modList;	//修正
		//Verfier m_verfier;			//验证器
		bool isTimeLimitBuff;			//限时BUFF
		float m_lifetime;				//作用时长
		float m_cycle;					//周期
		int m_cycleCount;				//周期数
		Name m_cycleEffect;				//周期效果
		//DamageResponse m_damageResponse;//伤害响应
	private:




	};

}