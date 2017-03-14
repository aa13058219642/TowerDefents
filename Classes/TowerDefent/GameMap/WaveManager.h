#pragma once
#include "stdfax.h"




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

