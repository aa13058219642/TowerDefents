#include "UnitManager.h"
#include "Tower.h"
#include "Monster.h"
#include "Bullet.h"
#include "DebugDraw.h"
#include "WaveManager.h"

UnitManager* UnitManager::p_myinstance = nullptr;
bool UnitManager::isDebug = false;

UnitManager::UnitManager()
{
	next_UnitID = 0;
	m_layer = nullptr;
}

UnitManager* UnitManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new UnitManager();
	}
	return p_myinstance;
}

Layer* UnitManager::getLayer()
{
	return m_layer;
}

void UnitManager::setLayer(Layer* layer)
{
	m_layer = layer;
}

void UnitManager::init()
{
	next_UnitID = 0;
}

void UnitManager::update(float dt)
{
	//更新Unit
	for (auto obj : m_UnitList)
		if (!(obj->getType() & Unit_Death))
			obj->update(dt);



	//删除要销毁的Unit
	for (auto iter = m_UnitList.begin(); iter != m_UnitList.end();)
	{
		Unit* obj = *iter;
		if (obj->getType() & Unit_Destory)
		{
			delete obj;
			iter = m_UnitList.erase(iter);
		}
		else
			iter++;
	}

	debugDraw();
}

Unit* UnitManager::getUnit(int id)
{
	for (auto var : m_UnitList)
	{
		if (var->ID == id)
			return var;
	}
	return nullptr;
}


vector<Unit*> UnitManager::findUnit(UnitType TypeFilter)
{
	vector<Unit*> vec;

	for (auto obj : m_UnitList)
	{
		//若A U B = A 则B含于A
		UnitType t = obj->getType();
		int x = t & TypeFilter;
		if ((obj->getType() & TypeFilter) == TypeFilter){
			vec.push_back(obj);
		}
	}
	return vec;
}

void UnitManager::addUnit(Unit* child)
{
	CCASSERT(child != nullptr, "UnitManager::addUnit :child==null");
	child->ID = next_UnitID++;
	child->bindActor();
	m_UnitList.push_back(child);
}

void UnitManager::removeUnit(Unit* child)
{
	if (child != nullptr)
	{
		delete child;
		m_UnitList.remove(child);
	}
}


void UnitManager::debugDraw()
{
	if (isDebug){
		//string str = StringUtils::format("DebugData:\ntower count:%d\nmonster count:%d\nbullet count:%d\nchild count:%d\n\n", 
		//towerList.size(), monsterList.size(), bulletList.size(), this->getChildrenCount());
		DebugDraw* debugdraw = DebugDraw::getInstance();

		string str = StringUtils::format("gameObj count = %d", m_UnitList.size());
		debugdraw->getLabel()->setString(str);

		DrawNode* debugDrawNode = debugdraw->getDrawNode();

		debugDrawNode->clear();
		for (auto var : m_UnitList){
			var->drawMyOutLine(debugDrawNode);
		}

		auto MonsterPath = GameMap::getInstance()->MonsterPath;
		int size = MonsterPath.size();
		for (int i = 0; i < size; i++)
		{
			MapPath path = MonsterPath[i];
			Vec2 last = path.getCurPos();

			for (int j = 1; j < path.getPosCount(); j++){
				path.NextPos();
				debugDrawNode->drawLine(last, path.getCurPos(), Color4F(1, 1, 1, 1));
				last = path.getCurPos();
			}
			
			if (MonsterPath[i].IsLoop())
				debugDrawNode->drawLine(last, path.getPos(path.getLoopTo()), Color4F(1, 1, 1, 1));
		}

	}
}






