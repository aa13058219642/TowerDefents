#include "GameObject.h"
#include "GameObjectLayer.h"

GameObject::GameObject()
{
	m_pos = Point(0, 0);
	m_isDeath = false;
	m_sprite = NULL;
}


GameObject::~GameObject()
{

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


GameObjectLayer* GameObject::getPatentLayer(){
	return (GameObjectLayer*)getParent();
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
void GameObject::onMissTarget(GameObject* target){}
void GameObject::onDead(){ m_isDeath = true; }
