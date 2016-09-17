#include "GridPos.h"
#include "Tower.h"

#include "TowerDefentShare.h"
#include "UnitManager.h"

GridPos::GridPos()
{
	ID = -1;
	m_type = EGridPosType::GridPosType_Empty;
	m_tower = nullptr;
	m_rect = Rect::ZERO;
	m_pos = Point::ZERO;
	m_dir = Direction::Center;
}

GridPos::GridPos(int id, Rect rect)
{
	ID = id;
	m_type = EGridPosType::GridPosType_Empty;
	m_tower = nullptr;
	m_rect = rect;
	m_pos = Point(m_rect.getMidX(), m_rect.getMidY());
}

GridPos::~GridPos()
{

}

EGridPosType GridPos::getType()
{
	return m_type;
}

Tower* GridPos::getTower()
{
	return m_tower;
}

const Rect& GridPos::getRect()
{
	return m_rect;
}

Point GridPos::getPos()
{
	return m_pos;
}

void GridPos::setAroundGridPosID(const int* around)
{
	for (int i = 0; i < 8; i++)
	{
		m_around[i] = around[i];
	}
}

void GridPos::setAroundGridPosID(Direction dir, int id)
{
	m_around[dir] = id;
}

const int* GridPos::getAroundGridPosID()
{
	return m_around;
}

int GridPos::getAroundGridPosID(Direction dir)
{
	return m_around[dir];
}


void GridPos::initTower()
{
	m_tower = new Tower(this);
	m_tower->setActorName("blank");
	UnitManager::getInstance()->addUnit(m_tower);
}

void GridPos::onClick()
{
	log("GridPos:(%f,%f)", m_pos.x, m_pos.y);
	NotificationMsg msg;
	msg.clear();

	switch (m_type)
	{
	case EGridPosType::GridPosType_Empty:
		msg["cmd"] = (int)MsgCMD::TowerSelectLayer_ClickEmptyGridPos;
		msg["GridPos"] = (int)this;
		msg["x"] = m_pos.x;
		msg["y"] = m_pos.y;
		NotificationCenter::getInstance()->postNotification(Message_TowerSelectLayer, (Ref*)&msg);
		break;

	case EGridPosType::GridPosType_Tower:
		msg["cmd"] = (int)MsgCMD::TowerSelectLayer_ClickTowerGridPos;
		msg["GridPos"] = (int)this;
		msg["x"] = m_pos.x;
		msg["y"] = m_pos.y;
		msg["color_r"] = (int)m_tower->getColor().r;
		msg["color_g"] = (int)m_tower->getColor().g;
		msg["color_b"] = (int)m_tower->getColor().b;
		NotificationCenter::getInstance()->postNotification(Message_TowerSelectLayer, (Ref*)&msg);
		break;

	case EGridPosType::GridPosType_SpellEmpty:
		msg["cmd"] = (int)MsgCMD::TowerSelectLayer_ClickSpellEmptyGridPos;
		msg["GridPos"] = (int)this;
		msg["x"] = m_pos.x;
		msg["y"] = m_pos.y;
		msg["color_r"] = (int)m_tower->getColor().r;
		msg["color_g"] = (int)m_tower->getColor().g;
		msg["color_b"] = (int)m_tower->getColor().b;
		NotificationCenter::getInstance()->postNotification(Message_TowerSelectLayer, (Ref*)&msg);
		break;

	case EGridPosType::GridPosType_SpellTower:
		msg["cmd"] = (int)MsgCMD::TowerSelectLayer_ClickSpellTowerGridPos;
		msg["GridPos"] = (int)this;
		msg["x"] = m_pos.x;
		msg["y"] = m_pos.y;
		msg["color_r"] = (int)m_tower->getColor().r;
		msg["color_g"] = (int)m_tower->getColor().g;
		msg["color_b"] = (int)m_tower->getColor().b;
		NotificationCenter::getInstance()->postNotification(Message_TowerSelectLayer, (Ref*)&msg);
		break;

	default:break;
	}
}

void GridPos::buildTower(int tid)
{
	m_type = EGridPosType::GridPosType_Tower;
	m_tower->buildTower(tid);
}

void GridPos::buildSpellPos(Tower* parent, Direction dirRelativeToTower)
{
	m_type = EGridPosType::GridPosType_SpellEmpty;
	m_tower = parent;
	m_dir = dirRelativeToTower;
}

void GridPos::buildSpellTower(int SpellTowerID)
{
	m_type = EGridPosType::GridPosType_SpellTower;
	m_tower->buildSpellTower(m_dir, SpellTowerID);
}

void GridPos::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_rect.getMinX(), m_rect.getMinY());
	point[1] = Vec2(m_rect.getMaxX(), m_rect.getMinY());
	point[2] = Vec2(m_rect.getMaxX(), m_rect.getMaxY());
	point[3] = Vec2(m_rect.getMinX(), m_rect.getMaxY());

	drawNode->drawPolygon(point, 4, Color4F(0, 1, 1, 0.5), 1, Color4F(0, 1, 1, 1));
}

