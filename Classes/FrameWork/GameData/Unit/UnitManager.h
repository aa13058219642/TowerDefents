#pragma once
#include "GalaxyBase.h"
#include "CUnit.h"

namespace cocosgalaxy
{
	class UnitManager
	{
	public:
		static bool isDebug;

		static UnitManager* getInstance();

		void init();
		void update(float dt);

		Layer* getLayer();
		void setLayer(Layer* layer);

		CUnit* getUnit(int id);
		void addUnit(CUnit* child);
		void removeUnit(CUnit* child);
		vector<CUnit*> findUnit(UnitType TypeFilter);

	private:
		int next_UnitID;
		static UnitManager* p_myinstance;
		Layer* m_layer;
		std::list<CUnit*> m_UnitList;

		UnitManager();
		void debugDraw();
	};
}


