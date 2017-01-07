#pragma once
#include "GalaxyBase.h"
#include "CGameData.h"
#include "CUnit.h"

namespace cocosgalaxy
{
	class CSkill : public CGameData
	{
	public:
		/* ---- Ù–‘---- */

		int ID;
		string name;


		/* ----∑Ω∑®---- */

		CSkill();
		~CSkill();
		virtual CSkill* clone() = 0;

		void setType(ESkillType type);
		ESkillType getType();

		void setParent(int parentID);
		CUnit* getParent();

		virtual void update(float dt) = 0;
		virtual bool IsCanExecute() = 0;

	protected:
		string groupID;
		ESkillType m_type;
		int m_parentID;
	};
}
