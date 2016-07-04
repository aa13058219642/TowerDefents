#pragma once
#include "stdfax.h"

class MapPath
{
public:
	BOOL isLoop = false;
	std::list<Point> pos;
};


class WaveData
{
public:
	int PathID = 0;
	int MonsterID = 0;
	float NextMonsterDalay = 0;
};

class Wave{
public:
	float WaveTimeLength = 0;
	vector<WaveData> wavedata;

};

class GameMap 
{
public:
	static GameMap* getInstance();

	bool LoadMap(int level);

	vector<Point> TowerPos;
	vector<MapPath> MonsterPath;
	vector<Wave> WaveList;

private:
	GameMap();
	static GameMap* p_myinstance;

	int Level;
	Size MapSize;

	template <typename T>
	void ReadData(T& dest,const void* src, int& p);
};



