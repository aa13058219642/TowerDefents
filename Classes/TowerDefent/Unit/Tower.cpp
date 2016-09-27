#include "TowerDefentShare.h"
#include "Tower.h"
#include "Actor.h"
#include "ActorManager.h"
#include "SkillManager.h"
#include "WeaponManager.h"
#include "BehaviorManager.h"
#include "GameMap.h"

Tower::~Tower()
{
}


Tower::Tower(GridPos* GridPos)
{
	bool flag = false;

	do{
		m_gridPos = GridPos;

		for (int i = 0; i < 8; i++)
			m_SpellTower[i] = nullptr;

		setPos(GridPos->getPos());
		setType( EUnitType::Unit_Tower);
		flag = true;
		
	} while (0);
}


Color3B Tower::getColor()
{
	return m_color;
}

void Tower::buildTower(int tid)
{
	Radius = 32;
	m_color = Color3B::RED;
	MP = AbilityEx<float>(1000, 0, 1000);
	AP = AbilityEx<float>(1000, 0, 1000);
	AP_RegenRate = 50;


	string act,wea;
	switch (tid)
	{
	case 0: act = "Tower_000"; wea = "wTower_000"; m_color = Color3B(255, 51, 255); break;
	case 1: act = "Tower_001"; wea = "wTower_001"; m_color = Color3B(153, 51, 153); break;
	case 2: act = "Tower_002"; wea = "wTower_002"; m_color = Color3B(51, 51, 153); break;
	case 3: act = "Tower_003"; wea = "wTower_003"; m_color = Color3B(102, 102, 204); break;
	case 4: act = "Tower_004"; wea = "wTower_004"; m_color = Color3B(204, 102, 204); break;
	case 5: act = "Tower_005"; wea = "wTower_005"; m_color = Color3B(255, 204, 255); break;
	case 6: act = "Tower_006"; wea = "wTower_006"; m_color = Color3B(51, 102, 255); break;
	case 7: act = "Tower_007"; wea = "wTower_007"; m_color = Color3B(153, 204, 255); break;
	default:break;
	}
	m_weapon = WeaponManager::getInstance()->getWeapon(wea);
	this->addSkill(SkillManager::getInstance()->createCSkill("attack", this));
	this->setActorName(act);

	this->bindActor();
	this->m_actor->setShowHpBar(true, Point(-32, 32), Size(64, 3));
}

void Tower::buildSpellTowerPos(Direction direction)
{
	//m_SpellTower[direction] = new SpellTower(this, direction);
	string str = StringUtils::format("spellPos%03d", (int)direction);
	m_actor->playEffect(str, 99999, m_color, Point::ZERO, -999);
}

void Tower::buildSpellTower(Direction direction, const SpellCard* spellTower)
{

	this->addBehavior(BehaviorManager::getInstance()->createBehavior(spellTower->behaviorName));

	GridPos* GridPos = GameMap::getInstance()->getGridPos(m_gridPos->getAroundGridPosID(direction));
	string str = StringUtils::format("SpellTower_%03d", spellTower->Icon);
	m_actor->playEffect(str, 99999, m_color, Point(GridPos->getPos() - m_pos), 0);
}

void Tower::sellSpellTower(Direction direction)
{
	//delete m_SpellTower[direction];
	//m_SpellTower[direction] = nullptr;
}

void Tower::sellTower()
{
	for (int i = 0; i < 8; i++)
		this->sellSpellTower((Direction)i);

	ActorManager::getInstance()->removeActor(ID);
}


void Tower::update(float dt)
{
	Unit::update(dt);

	//update Ability
	if (m_actorName != "blank")
	{
		HP += HP_RegenRate.getValue()*dt;
		MP += MP_RegenRate.getValue()*dt;
		AP += AP_RegenRate.getValue()*dt;
		this->m_actor->setHpBarProgress((float)AP / AP.Max);
	}
}

void Tower::onClick()
{
	//upgrade();
	m_gridPos->onClick();

}




void Tower::onAttack(Unit* target)
{

}

void Tower::onBindSprite()
{
	m_actor->setShowUnitPos(true);
}



void Tower::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(0, 1, 0, 0.5f), 1, Color4F(0, 1, 0, 1));
}





