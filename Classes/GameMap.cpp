#include "GameMap.h"

GameMap* GameMap::p_myinstance = NULL;
GameMap* GameMap::getInstance()
{
	if (p_myinstance == NULL)
	{
		p_myinstance = new GameMap();
	}
	return p_myinstance;
}

GameMap::GameMap()
{
	Level = -1;																		
}



bool GameMap::LoadMap(int level)
{
	FileUtils* fin = FileUtils::getInstance();

	//string filePath = fin->getWritablePath();
	string filePath = "";
	string fileName = StringUtils::format("map/level_%d.map",level);
	Data data = fin->getDataFromFile(filePath + fileName);
	byte* byt = data.getBytes();
	int p = 0;

	//MapSize
	ReadData(MapSize.width, byt, p);
	ReadData(MapSize.height, byt, p);

	//TowerPos
	int TowerPosCount, x, y;
	ReadData(TowerPosCount, byt, p);
	for (int i = 0; i < TowerPosCount; i++)
	{
		ReadData(x, byt, p);
		ReadData(y, byt, p);

		TowerPos.push_back(Point(x, y));
	}

	//MonsterPath
	int PathCount,PosCount;
	ReadData(PathCount, byt, p);

	for (int i = 0; i < PathCount; i++){
		MapPath path;
		ReadData(path.isLoop, byt, p);
		ReadData(PosCount, byt, p);

		for (int j = 0; j < PosCount; j++)
		{
			ReadData(x, byt, p);
			ReadData(y, byt, p);

			path.pos.push_back(Point(x, y));
		}
		MonsterPath.push_back(path);
	}

	//Wave
	int waveCount,waveDataCount;
	ReadData(waveCount, byt, p);
	
	for (int i = 0; i < waveCount; i++)
	{
		Wave wave;
		ReadData(wave.WaveTimeLength, byt, p);
		ReadData(waveDataCount, byt, p);
		for (int j = 0; j <waveDataCount; j++)
		{
			WaveData data;
			ReadData(data.PathID, byt, p);
			ReadData(data.MonsterID, byt, p);
			ReadData(data.NextMonsterDalay, byt, p);
			wave.wavedata.push_back(data);
		}
		WaveList.push_back(wave);
	}

	//delete[] byt;
	Level = level;

	return true;
}

template <typename T>
void GameMap::ReadData(T& dest, const void* src, int& p){
	memcpy(&dest, (char*)src+p, sizeof(dest));
	p += sizeof(dest);
}







