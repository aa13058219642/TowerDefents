#pragma once
#include "GalaxyBase.h"
#include "CUnit.h"
#include "UnitCreator.h"

namespace cocosgalaxy
{
	/*
	UnitManager
	管理游戏中所有的Unit对象的生命周期
	*/
	class UnitManager
	{
	public:
		static bool isDebug;

		static UnitManager* getInstance();

		//初始化Manager
		void init(UnitCreator* unitCreator = nullptr);
		void update(float dt);

		/*绑定UnitCreator（旧的会被释放）*/
		void bindUnitCreator(UnitCreator* unitCreator);
		/*根据typeID，使用绑定的UnitCreator创建Unit对象或它的子类*/
		CUnit* CreateUnit(int typeID);
		/*根据typeName，使用绑定的UnitCreator创建Unit对象或它的子类*/
		CUnit* CreateUnit(string typeName);

		/*根据ID获取Unit对象*/
		CUnit* getUnit(int id);
		/*添加Unit到Manager队列*/
		void addUnit(CUnit* child);
		
		/*移除并销毁Unit*/
		void removeUnit(CUnit* child);
		/*寻找一组特定类别的Unit*/
		vector<CUnit*> findUnit(UnitType TypeFilter);

	private:
		int next_UnitID;
		static UnitManager* p_myinstance;
		std::list<CUnit*> m_UnitList;
		UnitCreator* unitCreator;

		UnitManager();
		void debugDraw();
	};
}


