#include "GameMap.h"
#include "DebugDraw.h"
#include "MonsterManager.h"
#include "TowerDefentShare.h"
#include "GalaxyBase.h"
GameMap* GameMap::p_myinstance = nullptr;
GameMap* GameMap::getInstance()
{
	if (p_myinstance == nullptr)
	{
		p_myinstance = new GameMap();
	}
	return p_myinstance;
}

GameMap::GameMap()
{
	m_mapSize = Size::ZERO;
	m_map = nullptr;
	curWave = -1;
	curMonster = 0;

	waveTime = 0;
	monsterTime = 0;
}

GameMap::~GameMap()
{

}

void GameMap::clear()
{
	if (!m_gridPos.empty())
	{
		for (auto var : m_gridPos)
			delete var;
		m_gridPos.clear();
	}
	if (m_map != nullptr)
	{
		m_map->release();
		m_map = nullptr;
	}
	curWave = -1;
	curMonster = 0;

	waveTime = 0;
	monsterTime = 0;
	MonsterPath.clear();
	WaveList.clear();
}


bool GameMap::init(LevelData leveldata)
{
	m_leveldata = leveldata;
	this->clear();
	loadMap(leveldata.world, leveldata.level);

	this->msgSubscribe(Message_Global);
	//this->msgSubscribe(Message_GameMap);

	return true;
}

bool GameMap::loadMap(int wrold, int level)
{
	string fileName = StringUtils::format("map/map_%03d%03d.tmx", wrold, level);
	m_map = TMXTiledMap::create(fileName);
	m_map->retain();

	float scale = 1 / Director::getInstance()->getContentScaleFactor();

	//GridPos
	TMXObjectGroup* group = m_map->getObjectGroup("TowerPos");
	ValueVector vec = group->getObjects();
	m_gridPos.clear();
	m_gridPos.resize(vec.size());
	if (!vec.empty())
	{
		int i = 0;
		for (const auto& v : vec)
		{
			const ValueMap& dict = v.asValueMap();

			m_gridPos[i] = new GridPos(
				i,
				Rect(dict.at("x").asFloat(),
				dict.at("y").asFloat(),
				dict.at("width").asFloat(),
				dict.at("height").asFloat()));
			i++;
		}
	}
	//计算临近的塔的ID
	float h = group->getProperty("TowerPosHeight").asFloat() *scale;
	float w = group->getProperty("TowerPosWidth").asFloat() *scale;
	float dis = (h + 2)*(h + 2) + (w + 2)*(w + 2);
	vector<int> GridPosID;
	for (auto t1 : m_gridPos)
	{
		GridPosID.clear();
		Point pos = t1->getPos();
		for (auto t2 : m_gridPos)
		{
			if (t1 != t2 && pos.distanceSquared(t2->getPos()) <= dis)
			{
				GridPosID.push_back(t2->ID);
			}
		}

		int around[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
		for (auto tid : GridPosID)
		{
			Rect rect = m_gridPos[tid]->getRect();
			if (rect.containsPoint(Point(pos.x, pos.y + h)))around[North] = tid;
			else if (rect.containsPoint(Point(pos.x - w, pos.y + h)))around[NorthWest] = tid;
			else if (rect.containsPoint(Point(pos.x - w, pos.y)))around[West] = tid;
			else if (rect.containsPoint(Point(pos.x - w, pos.y - h)))around[SouthWest] = tid;
			else if (rect.containsPoint(Point(pos.x, pos.y - h)))around[South] = tid;
			else if (rect.containsPoint(Point(pos.x + w, pos.y - h)))around[SouthEast] = tid;
			else if (rect.containsPoint(Point(pos.x + w, pos.y)))around[East] = tid;
			else if (rect.containsPoint(Point(pos.x + w, pos.y + h)))around[NorthEast] = tid;
		}
		t1->setAroundGridPosID(around);
	}


	//MonsterPath
	group = m_map->getObjectGroup("Path");
	vec = group->getObjects();
	MonsterPath.clear();
	if (!vec.empty())
	{
		vector<Point> posvec;
		for (const auto& var : vec)
		{
			posvec.clear();
			const ValueMap& dict = var.asValueMap();
			const ValueVector& vec2 = dict.at("polylinePoints").asValueVector();
			Point pos = Point(dict.at("x").asFloat(), dict.at("y").asFloat());

			for (const auto& v : vec2)
			{
				const ValueMap& dict = v.asValueMap();
				posvec.push_back(Point(pos.x + dict.at("x").asFloat()*scale, pos.y - dict.at("y").asFloat()*scale));
				//posvec.push_back(Point(pos.x + dict.at("x").asFloat(), pos.y - dict.at("y").asFloat()));
			}
			MonsterPath.push_back(MapPath(dict.at("LoopTo").asInt(), posvec));
		}
	}

	//WaveData
	waveCount = m_map->getProperty("WaveCount").asInt();
	std::stringstream ss;
	string propertyName;
	WaveList.clear();
	for (int i = 1; i <= waveCount; i++)
	{
		propertyName = StringUtils::format("Wave%03d", i);
		group = m_map->getObjectGroup(propertyName);
		CCASSERT(group != nullptr, string("propertyName :" + propertyName + " NOT found").c_str());

		Wave wave;
		wave.WaveTime = group->getProperty("waveTime").asInt();

		int momsterCount = group->getProperty("momsterCount").asInt();
		for (int j = 1; j <= momsterCount; j++)
		{
			propertyName = StringUtils::format("m%03d", j);
			ss.clear();
			ss << group->getProperty(propertyName).asString();

			WaveData data;
			ss >> data.MonsterID;
			ss >> data.PathID;
			ss >> data.NextDalay;

			wave.wavedata.push_back(data);
		}
		WaveList.push_back(wave);
	}

	m_state = GS_Ready;
	return true;
}

void GameMap::receive(const Message* message)
{
	if (message->keyword == "GameOver")
	{
		m_state = GS_Fail;
		Message msg("show");
		msg.valueMap["iswin"] = false;
		msg.post(Message_LevelFinishLayer);
	}
}



TMXTiledMap*  GameMap::getMapLayer()
{
	return m_map;
}

GridPos* GameMap::getGridPos(int id)
{
	CCASSERT(id != -1 && id < (int)m_gridPos.size(), "GridPosID NOT found");
	return m_gridPos[id];
}

GridPos* GameMap::getGridPos(Point pos)
{
	for (auto var : m_gridPos)
	{
		if (var->getPos() == pos)
			return var;
	}
	return nullptr;
}

GameMap::EGameState GameMap::getState()
{
	return m_state;
}


void GameMap::bindActor()
{
	for (auto gird : m_gridPos)
	{
		gird->bindActor();
	}
}


void GameMap::SkipToNextWave()
{
	if (curWave == -1 ||
		(curWave < waveCount-1 && curMonster >= (int)WaveList[curWave].wavedata.size() && monsterTime > 3.0f))
	{

		waveTime = 0;
		m_state = GS_NextWave;
	}
}

void GameMap::UpdateNextWaveInfo()
{
	if (curWave < waveCount-1)
	{
		int nextwave = curWave + 1;

		map<int, string> map;
		for (auto m : WaveList[nextwave].wavedata)
		{
			if (map.find(m.MonsterID) == map.end())
			{
				map[m.MonsterID] = MonsterManager::getInstance()->getMonster(m.MonsterID)->name;
			}
		}

		string info = "";
		for (auto n : map)
		{
			info += n.second + "\n";
		}

		Message msg(Message_GameInfoLayer);
		msg.keyword = "updateNextWaveInfo";
		msg.valueMap["value"] = info;
		msg.post(Message_GameInfoLayer);
	}
}


void GameMap::update(float dt)
{
	if (m_state == GS_Pause || m_state == GS_Fail)
	{
		return;
	}

	waveTime -= dt;
	monsterTime -= dt;
	UnitManager::getInstance()->update(dt);


	if (m_state == GS_Ready)
	{

	}
	else if (m_state == GS_NextWave)
	{
		curWave++;
		if (curWave < waveCount)
		{
			//log("Wave---%d", curWave);
			monsterTime = 0;
			curMonster = 0;
			waveTime += WaveList[curWave].WaveTime;
			m_state = GS_CreatingMonster;
		}
		else{
			log("Wave End");
			m_state = GS_WaitToAllMonsterDie;
		}
	}
	else if (m_state == GS_CreatingMonster)
	{
		if (monsterTime <= dt)
		{
			if (curMonster < (int)WaveList[curWave].wavedata.size()){
				//log("Monster---%d", curMonster);

				UnitManager* objMgr = UnitManager::getInstance();

				Monster* monster = MonsterManager::getInstance()->CreateMonster(WaveList[curWave].wavedata[curMonster].MonsterID);
				monster->setMapPath(MonsterPath[WaveList[curWave].wavedata[curMonster].PathID]);
				monster->setPos(MonsterPath[WaveList[curWave].wavedata[curMonster].PathID].getCurPos());
				objMgr->addUnit(monster);

				monsterTime += WaveList[curWave].wavedata[curMonster].NextDalay;
				curMonster++;
			}
			else{
				//log("Monster End");
				monsterTime += 999999;
				m_state = GS_WaitToAllMonsterDie;

				if (curWave != -1)
				{
					UpdateNextWaveInfo();
				}
			}
		}
	}
	else if (m_state == GS_WaitToAllMonsterDie)
	{
		if (waveTime <= dt 
			|| false == UnitManager::getInstance()->hasUnitType(cocosgalaxy::EUnitType::Monster))
		{
			if (curWave < waveCount)
			{
				m_state = GS_WaitToNextWave;
				Message msg("updateWave");
				msg.valueMap["wave"] = curWave + 1;
				msg.valueMap["waveCount"] = waveCount;
				msg.post(Message_Global);
			}
			else
			{
				m_state = GS_Win;
			}
		}
	}
	else if (m_state == GS_WaitToNextWave)
	{
		if (waveTime <= dt)
		{
			curWave++;
			if (curWave < waveCount)
			{
				//log("Wave---%d", curWave);
				monsterTime = 0;
				curMonster = 0;
				waveTime += WaveList[curWave].WaveTime;
				m_state = GS_CreatingMonster;


				Message msg("updateWave");
				msg.valueMap["wave"] = curWave + 1;
				msg.valueMap["waveCount"] = waveCount;
				msg.post(Message_Global);
			}
			else{
				log("Wave End");
				waveTime += 999999;
				m_state = GS_WaitToAllMonsterDie;
			}
		}
	}
	else if (m_state == GS_Win)
	{
		log("Win!");
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);

		Player* player = Player::getInstance();

		float money2 = 0;
		for (auto grid : m_gridPos)
		{
			if (grid->getType() == EGridPosType::GridPosType_Tower)
			{
				money2 +=grid->getSellPrice();
			}
		}
		money2 += player->getMoney();


		Message msg("show");
		msg.valueMap["iswin"] = true;
		msg.valueMap["world"] = m_leveldata.world;
		msg.valueMap["level"] = m_leveldata.level;
		msg.valueMap["title"] = StringUtils::format("%d-%d %s", m_leveldata.world, m_leveldata.level, m_leveldata.title.c_str());
		msg.valueMap["money1"] = player->getLife() * 50.0f;
		msg.valueMap["money2"] = money2;
		msg.valueMap["money3"] = m_leveldata.awardMoney;
		msg.valueMap["money4"] = 0.0f;
		msg.valueMap["rank"] = player->getLife()/4;

		msg.post(Message_LevelFinishLayer);

		m_state = GS_WaitToEnd;
	}
	else if (m_state == GS_WaitToEnd)
	{

	}
}


bool GameMap::onClick(Point pos)
{
	for (auto grid : m_gridPos)
	{
		if (grid->isClickMe(pos))
		{
			grid->onClick();
			return true;

		}
	}
	return false;
}

