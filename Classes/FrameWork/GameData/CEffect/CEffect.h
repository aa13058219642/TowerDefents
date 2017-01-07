#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"
#include "CUnit.h"

namespace cocosgalaxy
{

	enum ECEffectState{
		ECEffectState_Unused,
		ECEffectState_Effting,
		ECEffectState_Death
	};

	class CEffect :public CGameData
	{
	public:

		/* ----属性---- */

		string id;
		float lifetime;
		UnitType filter;

		/* ----方法---- */

		CEffect();
		~CEffect();

		virtual CEffect* clone() = 0;
		virtual void execute() = 0;

		virtual bool Filtered(CUnit* obj);	//CUnit过滤，通过验证是返回true

		void update(float dt);


		virtual void setParent(int parentID);
		virtual CUnit* getParent();

		virtual void setTarget(int targetID);
		virtual CUnit* getTarget();

		void setState(ECEffectState state);
		ECEffectState getState();
		bool isDeath();
	protected:
		ECEffectState m_state;
		int m_parentID;
		int m_targetID;

	};

}