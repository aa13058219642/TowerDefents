#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"
#include "CCostUnit.h"
#include "CUnit.h"

namespace cocosgalaxy
{

	enum EBehaviorType{
		ECBehavior,
		ECBeahaviorBuff
	};

	class CBehavior : public CGameData
	{
	public:
		int id;
		Name name;
		CCostUnit cost;
		//Requirement


		enum EBehaviorState{
			EBehaviorState_Unused,
			EBehaviorState_Using,
			EBehaviorState_Death
		};

		CBehavior();
		~CBehavior();

		virtual CBehavior* clone() = 0;
		virtual bool meetRequirement() = 0;
		virtual void Install(CUnit* parent) = 0;
		virtual void Uninstall(CUnit* parent) = 0;
		virtual void update(float dt) = 0;

		//void setParent(CUnit* parent);
		EBehaviorType getType();
		bool isDeath();
	protected:
		EBehaviorType m_type;
		EBehaviorState m_state;
		CUnit* m_parent;
	};

}