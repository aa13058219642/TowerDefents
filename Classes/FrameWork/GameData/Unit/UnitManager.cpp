#include "UnitManager.h"
using namespace cocosgalaxy;

UnitManager* UnitManager::p_myinstance = nullptr;
bool UnitManager::isDebug = false;

UnitManager::UnitManager()
{
	next_UnitID = 0;
	unitCreator = nullptr;
	isInit = false;
}

UnitManager::~UnitManager()
{
	removeAllUnit();
	if (unitCreator != nullptr)
	{
		this->unitCreator = unitCreator;
	}
}


UnitManager* UnitManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new UnitManager();
	}
	return p_myinstance;
}


void UnitManager::init(UnitCreator* unitCreator)
{
	next_UnitID = 0;
	if (unitCreator == nullptr)
	{
		this->unitCreator = new UnitCreator();
	}
	else
	{
		this->unitCreator = unitCreator;
	}

	isInit = true;
}

void UnitManager::update(float dt)
{
	CCASSERT(isInit, "the UnitManager is NOT init !");

	//更新CUnit
	for (auto obj : m_UnitList)
		if (!(obj->getType() & EUnitType::Death))
			obj->update(dt);



	//删除要销毁的CUnit
	for (auto iter = m_UnitList.begin(); iter != m_UnitList.end();)
	{
		CUnit* obj = *iter;
		if (obj->getType() & EUnitType::Destory)
		{
			delete obj;
			iter = m_UnitList.erase(iter);
		}
		else
			iter++;
	}

	debugDraw();
}

void UnitManager::bindUnitCreator(UnitCreator* unitCreator)
{
	CCASSERT(isInit, "the UnitManager is NOT init !");

	if (this->unitCreator != nullptr)
	{
		delete this->unitCreator;
	}
	this->unitCreator = unitCreator;
}

CUnit* UnitManager::CreateUnit(int classHash, string typeName)
{
	return static_cast<CUnit*>(unitCreator->Create(classHash, typeName));
}

CUnit* UnitManager::CreateUnit(string className, string typeName)
{
	return static_cast<CUnit*>(unitCreator->Create(className, typeName));
}


CUnit* UnitManager::getUnit(int id)
{
	for (auto var : m_UnitList)
	{
		if (var->ID == id)
			return var;
	}
	return nullptr;
}


vector<CUnit*> UnitManager::findUnit(UnitType TypeFilter)
{
	vector<CUnit*> vec;

	for (auto obj : m_UnitList)
	{
		//若A U B = A 则B含于A
		UnitType t = obj->getType();
		int x = t & TypeFilter;
		if ((obj->getType() & TypeFilter) == TypeFilter)
		{
			vec.push_back(obj);
		}
	}
	return vec;
}

bool UnitManager::hasUnitType(UnitType TypeFilter)
{
	bool flag = false;

	for (auto obj : m_UnitList)
	{
		//若A U B = A 则B含于A
		UnitType t = obj->getType();
		int x = t & TypeFilter;
		if ((obj->getType() & TypeFilter) == TypeFilter)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

void UnitManager::addUnit(CUnit* child)
{
	CCASSERT(child != nullptr, "UnitManager::addUnit :child==null");
	child->ID = next_UnitID++;
	child->bindActor();
	m_UnitList.push_back(child);
}

void UnitManager::removeUnit(CUnit* child)
{
	if (child != nullptr)
	{
		delete child;
		m_UnitList.remove(child);
	}
}

void UnitManager::removeAllUnit()
{
	if (!m_UnitList.empty())
	{
		for (auto var : m_UnitList)
		{
			delete var;
		}
		m_UnitList.clear();
	}
}


void UnitManager::debugDraw()
{
	//if (isDebug){
	//	//string str = StringUtils::format("DebugData:\ntower count:%d\nmonster count:%d\nbullet count:%d\nchild count:%d\n\n", 
	//	//towerList.size(), monsterList.size(), bulletList.size(), this->getChildrenCount());
	//	DebugDraw* debugdraw = DebugDraw::getInstance();
	//	string str = StringUtils::format("gameObj count = %d", m_UnitList.size());
	//	debugdraw->getLabel()->setString(str);
	//	DrawNode* debugDrawNode = debugdraw->getDrawNode();
	//	debugDrawNode->clear();
	//	for (auto var : m_UnitList){
	//		var->drawMyOutLine(debugDrawNode);
	//	}
	//	auto MonsterPath = GameMap::getInstance()->MonsterPath;
	//	int size = MonsterPath.size();
	//	for (int i = 0; i < size; i++)
	//	{
	//		MapPath path = MonsterPath[i];
	//		Vec2 last = path.getCurPos();
	//		for (int j = 1; j < path.getPosCount(); j++){
	//			path.NextPos();
	//			debugDrawNode->drawLine(last, path.getCurPos(), Color4F(1, 1, 1, 1));
	//			last = path.getCurPos();
	//		}
	//		
	//		if (MonsterPath[i].IsLoop())
	//			debugDrawNode->drawLine(last, path.getPos(path.getLoopTo()), Color4F(1, 1, 1, 1));
	//	}
	//}
}






