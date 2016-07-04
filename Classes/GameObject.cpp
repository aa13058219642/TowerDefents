#include "GameObject.h"

GameObject::GameObject()
{
	m_pos = Point(0, 0);
	m_isDeath = false;
	m_sprite = NULL;
}


GameObject::~GameObject()
{

}


GameObject* GameObject::create(Point pos)
{
	GameObject* gameObject = new GameObject();
	if (gameObject && gameObject->init(pos))
	{
		gameObject->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(gameObject);
	}
	return gameObject;
}


bool GameObject::init(Point pos)
{
	bool flag = false;

	do{
		m_ability.Radius = 32;
		cur_ability = m_ability;

		setPos(pos);
		this->setPosition(pos);

		flag = true;
	} while (0);

	return flag;
}

bool GameObject::isClickMe(Point pos)
{
	Point srcPos, descPos;

	srcPos = Point(m_pos.x - cur_ability.Radius, m_pos.y + cur_ability.Radius);
	descPos = Point(m_pos.x + cur_ability.Radius, m_pos.y - cur_ability.Radius);
	if (pos.x >= srcPos.x &&
		pos.x <= descPos.x &&
		pos.y <= srcPos.y &&
		pos.y >= descPos.y){
		return true;
	}



	return false;
}

void GameObject::bindSprite(Sprite* sprite)
{
	if (m_sprite != NULL){
		m_sprite->removeFromParentAndCleanup(true);
	}
	m_sprite = sprite;
	this->addChild(sprite);
	this->setContentSize(sprite->getContentSize());

	onBindSprite();
}

Sprite* GameObject::getSprite()
{
	return m_sprite;
}

void GameObject::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[1] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[2] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y - cur_ability.Radius);
	point[3] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y - cur_ability.Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 1, 1, 0.3), 1.0F, Color4F(1, 1, 1, 1));
}


bool GameObject::isDead()
{
	return m_isDeath;
}

void GameObject::onBindSprite(){}
void GameObject::onAttack(){}
void GameObject::onBeAttack(int damage){}
void GameObject::onMove(){}
void GameObject::onHitTarget(){}
void GameObject::onDead(){ m_isDeath = true; }
