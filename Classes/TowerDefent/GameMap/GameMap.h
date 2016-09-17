#pragma once
#include "stdfax.h"
#include "WaveManager.h"
#include "GridPos.h"


class GameMap 
{
public:
	vector<MapPath> MonsterPath;
	vector<Wave> WaveList;

	static GameMap* getInstance();
	bool init(int level);
	void update(float dt);
	
	/*if something be click will return ture*/
	//bool onClick(Point pos);

	TMXTiledMap* getMapLayer();
	GridPos* getGridPos(int id);
	GridPos* getGridPos(Point pos);

private:
	GameMap();
	void clear();
	static GameMap* p_myinstance;

	int m_level;
	Size m_mapSize;
	TMXTiledMap* m_map;

	vector<GridPos*> m_gridPos;

	bool loadMap(const int& level);
	bool initMap(int level);


	//bool LoadMap(int level);
	//template <typename T>
	//void ReadData(T& dest,const void* src, int& p);
};



