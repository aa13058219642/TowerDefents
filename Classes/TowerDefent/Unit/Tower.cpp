#include "TowerDefentShare.h"
#include "Tower.h"
#include "TDUnitCreator.h"
#include "CActor.h"
#include "ActorManager.h"
#include "SkillManager.h"

#include "GameMap.h"
#include "Bullet.h"
#include "GameConfig.h"

Tower::~Tower()
{
}


Tower::Tower(GridPos* GridPos)
{
	bool flag = false;

	do{
		m_gridPos = GridPos;

		spellPosCount = 0;
		setPos(GridPos->getPos());
		setType( EUnitType::Tower);
		flag = true;
		
		m_TowerCard = TowerCard();
		for (int i = 0; i < 8; i++)
		{
			m_SpellTower[i] = nullptr;
		}

		m_spellactor = nullptr;
	} while (0);
}

void Tower::setTarget(int targetID)
{
	this->m_targetID = targetID;

	CUnit *target = UnitManager::getInstance()->getUnit(targetID);
	this->m_targetPos = target->getPos();
	//¸Ä±ä³¯Ïò
	if (target->getPos().x <= m_pos.x)
	{
		m_actor->changeFace(CActor::Face::FACE_TO_LEFT);
	}
	else
	{
		m_actor->changeFace(CActor::Face::FACE_TO_RIGHT);
	}
}

Color3B Tower::getColor()
{
	return m_color;
}

TowerCard Tower::getTowerCard()
{
	return m_TowerCard;
}

const SpellCard* Tower::getSpellCard(Direction direction)
{
	return m_SpellTower[direction];

}

int Tower::getSpellPosCount()
{
	return spellPosCount;
}

float Tower::getSumPrice()
{
	float sum = m_TowerCard.price.money;
	for (int i = 0; i < 8; i++)
	{
		if (m_SpellTower[i] != nullptr)
		{
			sum += m_SpellTower[i]->price.money;
		}
	}
	return sum;
}

float Tower::getSellPrice()
{
	return getSumPrice()* SellPercent;
}

float Tower::getSellSpellPosPrice(Direction direction)
{
	return (m_TowerCard.spellPosPrice[direction] + (spellPosCount - 1)*SpellPosPriceAddition)*SellPercent;
}


void Tower::buildTower(const TowerCard towerCard)
{
	Radius = 32;
	m_TowerCard = towerCard;
	spellPosCount = 0;

	m_color = towerCard.color;
	HP = AbilityEx<float>(towerCard.HP, 0, towerCard.HP);
	MP = AbilityEx<float>(towerCard.MP, 0, towerCard.MP);
	AP = AbilityEx<float>(towerCard.AP, 0, towerCard.AP);
	HP_RegenRate = towerCard.HP_RegenRate;
	MP_RegenRate = towerCard.MP_RegenRate;
	AP_RegenRate = towerCard.AP_RegenRate;

	this->setWeapon(towerCard.weaponName[0]);
	for (const string& skillname : towerCard.skillName)
	{
		this->addSkill(skillname);
	}

	this->setActorName(towerCard.ActorName);
	this->bindActor();
	//m_actor->setShowHpBar(true, Point(-32, 32), Size(64, 3));
	m_actor->setLocalLevel(2);

	m_spellactor = ActorManager::getInstance()->createActor(INT_MAX - ID, "blank");
	m_spellactor->setLocalLevel(1);
	m_spellactor->setPos(m_pos);
}

void Tower::buildSpellTowerPos(Direction direction)
{
	string name = StringUtils::format("spellPos%03d", (int)direction);
	m_spellactor->playEffect(name, FLT_MAX, m_color, Point::ZERO, 0, direction);

	m_TowerCard.price.money += m_TowerCard.spellPosPrice[direction] + spellPosCount*SpellPosPriceAddition;
	spellPosCount++;
}

void Tower::buildSpellTower(Direction direction, const SpellCard spellTower)
{
	this->addBehavior(spellTower.behaviorName);

	GridPos* GridPos = GameMap::getInstance()->getGridPos(m_gridPos->getAroundGridPosID(direction));
	string name = StringUtils::format("SpellTower_%03d", spellTower.ID);
	m_spellactor->playEffect(name, FLT_MAX, m_color, Point(GridPos->getPos() - m_pos), 0, direction);

	m_SpellTower[direction] = new SpellCard(spellTower);
}


void Tower::sellTower()
{
	for (int i = 0; i < 8; i++)
	{
		if (m_SpellTower[(Direction)i] != nullptr)
		{
			this->sellSpellTower((Direction)i);
		}
	}

	this->setWeapon(nullptr);

	this->setActorName("blank");
	this->bindActor();

	ActorManager::getInstance()->removeActor(INT_MAX - ID);
	this->onDead();
}

void Tower::sellSpellPos(Direction direction)
{
	string name = StringUtils::format("spellPos%03d", (int)direction);
	m_spellactor->removeEffect(name, direction);

	spellPosCount--;
	m_TowerCard.price.money -= m_TowerCard.spellPosPrice[direction] + spellPosCount*SpellPosPriceAddition;
}

void Tower::sellSpellTower(Direction direction)
{
	this->removeBehavior(m_SpellTower[direction]->behaviorName);
	string name = StringUtils::format("SpellTower_%03d", m_SpellTower[direction]->ID);
	m_spellactor->removeEffect(name, direction);

	delete m_SpellTower[direction];
	m_SpellTower[direction] = nullptr;
}

void Tower::update(float dt)
{
	CUnit::update(dt);

	//update Ability
	if (m_actorName != "blank")
	{
		HP += HP_RegenRate.getValue()*dt;
		MP += MP_RegenRate.getValue()*dt;
		AP += AP_RegenRate.getValue()*dt;
		//this->m_actor->setHpBarProgress((float)AP / AP.Max);
	}
}

void Tower::onClick()
{
	//upgrade();
	m_gridPos->onClick();

}

void Tower::onAttack(CUnit* target)
{
	Bullet* bullet = new Bullet(m_weapon, this->ID, target->ID, this->getPos());
	UnitManager::getInstance()->addUnit(bullet);
}

void Tower::onBindSprite()
{
	//m_actor->setShowUnitPos(true);
}

void Tower::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - Radius, m_pos.y + Radius);
	point[1] = Vec2(m_pos.x + Radius, m_pos.y + Radius);
	point[2] = Vec2(m_pos.x + Radius, m_pos.y - Radius);
	point[3] = Vec2(m_pos.x - Radius, m_pos.y - Radius);

	drawNode->drawPolygon(point, 4, Color4F(0, 1, 0, 0.5f), 1, Color4F(0, 1, 0, 1));
}





