#pragma once
#include "Unit.h"
#include "EnumConst.h"
#include <list>

class UnitManager
{
public:
	static bool isDebug;

	static UnitManager* getInstance();

	void init();
	void update(float dt);

	Layer* getLayer();
	void setLayer(Layer* layer);

	Unit* getUnit(int id);
	void addUnit(Unit* child);
	void removeUnit(Unit* child);
	vector<Unit*> findUnit(UnitType TypeFilter);
	
private:
	int next_UnitID;
	static UnitManager* p_myinstance;
	Layer* m_layer;
	std::list<Unit*> m_UnitList;

	UnitManager();
	void debugDraw();
};



