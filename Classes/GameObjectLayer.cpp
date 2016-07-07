#include "GameObjectLayer.h"
#include "TowerBase.h"
#include "MonsterBase.h"
#include "Bullet.h"

GameObjectLayer::GameObjectLayer()
{
	isDebug = false;
	curWave = -1;
	curWaveMonster = 0;
}

GameObjectLayer* GameObjectLayer::create(bool isDebug)
{
	GameObjectLayer* towerBase = new GameObjectLayer();
	if (towerBase && towerBase->init(isDebug))
	{
		towerBase->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(towerBase);
	}
	return towerBase;
}

bool GameObjectLayer::init(bool isDebug)
{
	bool flag = false;

	do{
		//初始化塔的位置
		TowerBase* tower;
		for (auto var : GameMap::getInstance()->TowerPos)
		{
			tower = TowerBase::create(var, isDebug);
			gameObjectList.pushBack(tower);
			addGameObject(tower);
		}

		WaveList = GameMap::getInstance()->WaveList;

		//初始化定时器
		this->scheduleUpdate();
		//this->scheduleOnce(schedule_selector(GameObjectLayer::CreateWave), 3.0f);
		RunDelayAction(callfunc_selector(GameObjectLayer::CreateWave), 3.0f);

		//debug模式
		this->isDebug = isDebug;
		if (isDebug){

			debugLabel = Label::createWithTTF("debugdata:","fonts/arial.ttf",16);
			debugLabel->setAnchorPoint(Point(0,1));
			debugLabel->setPosition(0, 832);
			this->addChild(debugLabel,999);

			debugDrawNode = DrawNode::create();
			this->addChild(debugDrawNode);
		}
		flag = true;
	} while (0);

	return flag;
}

void GameObjectLayer::update(float dt){
	DebugDraw();
}


GameObject* GameObjectLayer::findGameObject(Point pos, GameObjectType type)
{

	for (auto var : gameObjectList)
	{
		if (var->getObjectType()==type && var->isClickMe(pos))
			return (TowerBase*)var;
	}
	return NULL;
}

void GameObjectLayer::RunDelayAction(SEL_CallFunc selector, float delayTime){
	DelayTime * delayAction = DelayTime::create(delayTime);
	CallFunc * callFunc = CallFunc::create(this, selector);
	this->runAction(Sequence::createWithTwoActions(delayAction, callFunc));
}

void GameObjectLayer::CreateWave(){
	curWave++;

	int wavecount = WaveList.size();
	if (curWave < wavecount)
	{
		log("Wave---%d", curWave);
		RunDelayAction(callfunc_selector(GameObjectLayer::CreateWave), WaveList[curWave].WaveTimeLength);
		RunDelayAction(callfunc_selector(GameObjectLayer::CreateMonster), 0);
	}
	else{
		log("Wave End");
	}

}

void GameObjectLayer::CreateMonster(){
	int monsterCount = WaveList[curWave].wavedata.size();

	if (curWaveMonster < monsterCount){
		log("Monster---%d", curWaveMonster);

		MonsterBase* monster = MonsterBase::create(WaveList[curWave].wavedata[curWaveMonster].MonsterID, GameMap::getInstance()->MonsterPath[ WaveList[curWave].wavedata[curWaveMonster].PathID]);
		addGameObject(monster);

		RunDelayAction(callfunc_selector(GameObjectLayer::CreateMonster), WaveList[curWave].wavedata[curWaveMonster].NextMonsterDalay);
		curWaveMonster++;
	}
	else{
		curWaveMonster = 0;
		log("Monster End");
	}
}


void GameObjectLayer::addGameObject(GameObject* child)
{
	gameObjectList.pushBack(child);
	addChild(child);
}

void GameObjectLayer::removeGameObject(GameObject* child)
{
	gameObjectList.eraseObject(child);
	removeChild(child, true);
}


void GameObjectLayer::DebugDraw()
{
	if (isDebug){
		//string str = StringUtils::format("DebugData:\ntower count:%d\nmonster count:%d\nbullet count:%d\nchild count:%d\n\n", 
		//	towerList.size(), monsterList.size(), bulletList.size(), this->getChildrenCount());
		string str = StringUtils::format("gameObj count = %d", gameObjectList.size());
		debugLabel->setString(str);


		debugDrawNode->clear();
		for (auto var : gameObjectList){
			var->drawMyOutLine(debugDrawNode);
		}

		auto MonsterPath = GameMap::getInstance()->MonsterPath;
		int size = MonsterPath.size();
		for (int i = 0; i < size; i++)
		{
			Vec2 last;
			if (MonsterPath[i].isLoop)
				last = MonsterPath[i].pos.back();
			else
				last = MonsterPath[i].pos.front();

			for (auto cur : MonsterPath[i].pos){
				debugDrawNode->drawLine(last, cur, Color4F(1, 1, 1, 1));
				last = cur;
			}
		}

	}
}














