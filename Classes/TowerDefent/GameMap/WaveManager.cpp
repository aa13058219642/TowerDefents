#include "WaveManager.h"
#include "GameMap.h"
#include "Monster.h"
#include "UnitManager.h"






WaveManager* WaveManager::p_myinstance = nullptr;

WaveManager* WaveManager::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new WaveManager();
	}
	return p_myinstance;
}


WaveManager::WaveManager()
{
	//monsterPath = nullptr;
}


WaveManager::~WaveManager()
{

}

void WaveManager::init()
{
	startDelay = 10.0f;
	curWave = -1;
	curMonster = 0;

	waveTime = startDelay;
	monsterTime = startDelay;

	GameMap* gamemap = GameMap::getInstance();
	monsterPath = gamemap->MonsterPath;
	waveList = gamemap->WaveList;
}


void WaveManager::update(float dt)
{
	if (curWave < (int)waveList.size())
	{
		//Wave
		if (waveTime <= dt)
		{
			curWave++;
			if (curWave < (int)waveList.size())
			{
				//log("Wave---%d", curWave);
				monsterTime = 0;
				curMonster = 0;
				waveTime += waveList[curWave].WaveTime;
			}
			else{
				log("Wave End");
			}
		}
		waveTime -= dt;

		//Monster
		if (monsterTime <= dt)
		{
			if (curMonster < (int)waveList[curWave].wavedata.size()){
				//log("Monster---%d", curMonster);

				UnitManager* objMgr = UnitManager::getInstance();
				Monster* monster = new Monster(
					waveList[curWave].wavedata[curMonster].MonsterID, 
					monsterPath[waveList[curWave].wavedata[curMonster].PathID]);

				monster->setActorName("m001");
				objMgr->addUnit(monster);


				monsterTime += waveList[curWave].wavedata[curMonster].NextDalay;
				curMonster++;
			}
			else{
				//log("Monster End");
				monsterTime += 999999;
			}
		}
		monsterTime -= dt;
	}
}
