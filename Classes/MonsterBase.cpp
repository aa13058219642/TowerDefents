#include "MonsterBase.h"
#include "GameObjectLayer.h"

MonsterBase::MonsterBase()
{
	type = 0;
}


MonsterBase::~MonsterBase()
{

}


MonsterBase* MonsterBase::create(int MonsterID, MapPath path, bool isDebug)
{
	MonsterBase* monsterBase = new MonsterBase();
	if (monsterBase && monsterBase->init(MonsterID, path, isDebug))
	{
		monsterBase->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monsterBase);
	}
	return monsterBase;
}


bool MonsterBase::init(int MonsterID, MapPath path, bool isDebug)
{
	bool flag = false;

	do{

		//MonsterID
		//get m_alility from MonsterID
		m_ability.HP = 300;
		m_ability.MaxHP = 300;
		m_ability.Radius = 32;
		m_ability.Speed = 200;
		cur_ability = m_ability;

		createAnimate(MonsterID);

		auto sprite = Sprite::create();
		//////sprite->runAction(ActionManager::)
		this->bindSprite(sprite);


		///////

		setPos(path.pos.front());
		setPosition(m_pos);
		setMovePath(path);
		m_path.pos.pop_front();


		this->scheduleUpdate();
		flag = true;
	} while (0);

	return flag;
}


void MonsterBase::createAnimate(int MonsterID)
{

}


void MonsterBase::update(float dt){
	onMove(dt);
}


void MonsterBase::drawMyOutLine(DrawNode* drawNode){
	Point point[4];
	point[0] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[1] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y + cur_ability.Radius);
	point[2] = Vec2(m_pos.x + cur_ability.Radius, m_pos.y - cur_ability.Radius);
	point[3] = Vec2(m_pos.x - cur_ability.Radius, m_pos.y - cur_ability.Radius);

	drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 0.3f), 1.0F, Color4F(1, 0, 0, 1));
}


void MonsterBase::onMove(float dt)
{
	if (m_path.pos.size() == 0){
		//log("Move To Endding");
	}
	else
	{
		float dis = m_pos.distance(m_path.pos.front());

		if (dis <= 0)
		{
			m_path.pos.pop_front();
			if (m_path.pos.size() != 0)
			{
				dis = m_pos.distance(m_path.pos.front());
			}
			else{
				OnEndPoint();
				return;
			}
		}

		float move = cur_ability.Speed*dt;
		float a = move / dis;

		if (a >= 1)a = 1;
		m_pos = a*(m_path.pos.front() - m_pos) + m_pos;
		setPosition(m_pos);

	}
}

void MonsterBase::OnEndPoint(){
	log("Move To Endding");
	onDead();
}

void MonsterBase::onBeAttack(int damage)
{
	cur_ability.HP -= damage;
	float per = cur_ability.HP / (float)cur_ability.MaxHP;

	Size size = this->getContentSize();
	m_hpBar->setContentSize(Size(size.width*per, 6));


	if (cur_ability.HP <= 0){
		onDead();
	}
}

void MonsterBase::onBindSprite()
{



	//std::string file = StringUtils::format("monster/m_%d.png", MonsterID);
	std::string img = StringUtils::format("monster/m_%d.png", 1);
	std::string plist = StringUtils::format("monster/m_%d.plist", 1);


	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(plist, img);

	int count = 8;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= count; i++){
		string str = StringUtils::format("m_1_%d.png", i);
		frame = frameCache->getSpriteFrameByName(str);
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	getSprite()->runAction(action);


	//init HpBar
	m_hpBar = Scale9Sprite::create("UI/hpBar.png");
	//Rect rect = frame->getRect();
	this->setContentSize(frame->getRect().size);
	Size size = this->getContentSize();
	m_hpBar->setContentSize(Size(size.width, 6));
	m_hpBar->setPosition(-size.width / 2, size.height / 2);
	m_hpBar->setAnchorPoint(Point(0, 0.5));
	this->addChild(m_hpBar);
}


void MonsterBase::onDead()
{
	log("Monster Deadth!");
	GameObject::onDead();
	GameObjectLayer* parent = (GameObjectLayer*)getParent();

	for (auto var : parent->bulletList){
		var->onMissTarget(this);
	}

	parent->monsterList.eraseObject(this);
	this->removeFromParent();
}
