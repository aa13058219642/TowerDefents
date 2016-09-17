#pragma once
#include "stdfax.h"

class WaveData
{
public:
	int PathID = 0;
	int MonsterID = 0;
	float NextDalay = 0;
};

class Wave{
public:
	float WaveTime = 0;
	vector<WaveData> wavedata;

};
#define IS_NOT_LOOP_PATH -1
class MapPath
{
public:
	MapPath(){}
	MapPath(int loopTo, std::vector<Point> pos){ this->loopTo = loopTo; this->pos = pos; }

	bool IsLoop(){ return loopTo != IS_NOT_LOOP_PATH; }
	/*if no next will return false */
	bool IsHasNext(){ return loopTo != IS_NOT_LOOP_PATH || curPos < (int)pos.size()-1; }
	
	void NextPos()
	{ 
		curPos++; 
		if (curPos >= (int)pos.size())
			curPos = loopTo; 
	}
	Point getCurPos(){ return pos[curPos]; }
	int getPosCount(){ return (int)pos.size(); }
	Point getPos(int index){ return pos[index]; }
	int getLoopTo(){ return loopTo; }
private:
	int curPos = 0;
	int loopTo = IS_NOT_LOOP_PATH;
	std::vector<Point> pos;
};

class WaveManager
{
public:
	static WaveManager* getInstance();
	~WaveManager();

	void update(float dt);
	void init();

private:
	static WaveManager* p_myinstance;

	float startDelay;
	float waveTime;
	float monsterTime;

	int curWave;
	int curMonster;

	vector<MapPath> monsterPath;
	vector<Wave> waveList;


	WaveManager();
	void createWave();
	void createMonster();
};

