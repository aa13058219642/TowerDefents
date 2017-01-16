#include "Monster.h"
#include "CActor.h"
#include "AnimateManager.h"
#include "UnitManager.h"
#include "TowerDefentShare.h"
#include "Message\Message.h"

//Monster::Monster()
//{
//
//}


Monster::~Monster()
{

}


Monster::Monster(int MonsterID, MapPath path)
{
	bool flag = false;

	do{

		//MonsterID
		setType(5);
		//get m_alility from MonsterID
		HP = 100;
		HP.Max = 100;
		Radius = 32;
		Speed = 100;




		setPos(path.getCurPos());
		setMovePath(path);

		flag = true;
	} while (0);
}


void Monster::update(float dt){
	CUnit::update(dt);

	onMove(dt);
}


void Monster::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 0.3f), 1.0F, Color4F(1, 0, 0, 1));
}


void Monster::onMove(float dt)
{
	if (m_path.getPosCount() > 0)
	{
		float dis = m_pos.distance(m_path.getCurPos());

		if (dis <= 0)
		{
			if (!m_path.IsHasNext())
			{
				OnEndPoint();
				return;
			}
			m_path.NextPos();
			dis = m_pos.distance(m_path.getCurPos());
		}

		float move = Speed.getValue()*dt;
		float a = move / dis;

		if (a > 1)a = 1;
		m_pos = a*(m_path.getCurPos() - m_pos) + m_pos;
		m_actor->setPos(m_pos);
	}
}

void Monster::OnEndPoint(){
	//log("Move To Endding");
	onDead();
}

void Monster::onBeAttack(int damage, EDamageType damageType)
{
	if (!(m_type & EUnitType::Death))
	{
		HP.add(-damage);
		float per = clampf(HP / (float)HP.Max, 0, 1);
		
		//m_hpBar->setContentSize(Size(64*per, 6));
		m_actor->setHpBarProgress(per);

		if (HP <= 0){
			onDead();
		}
	}
}

void Monster::onBindSprite()
{
	m_actor->setShowHpBar(true, Point(-32, 100), Size(64, 6));
}


void Monster::onDead()
{
	CUnit::onDead();

	//NotificationMsg msg;
	//msg["cmd"] = GameMap_addMoney;
	//msg["addMoney"] = 100;
	//NotificationCenter::getInstance()->postNotification(Message_GameMap, (Ref*)&msg);

	Message msg;
	msg.keyword = "Money";
	msg.valueMap["value"] = 10;
	msg.post(Message_Player);
}
