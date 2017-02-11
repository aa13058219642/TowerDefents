#include "GameMap.h"
#include "DebugDraw.h"

#include "TextureManager.h"
#include "AnimateManager.h"
#include "UnitManager.h"
#include "WaveManager.h"
#include "ActorManager.h"
#include "WeaponManager.h"
#include "EffectManager.h"
#include "SkillManager.h"
#include "BehaviorManager.h"
#include "SpellCardManager.h"
#include "TowerCardManager.h"
#include "TDUnitCreator.h"
#include "Player.h"

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
	m_level = -1;
	m_mapSize = Size::ZERO;
	m_map = nullptr;

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

}


bool GameMap::init(int level)
{
	CCASSERT(level != -1, "illgle level !");
	m_level = level;
	
	this->clear();

	//this->LoadMap(level);//<-----

	loadMap(m_level);
	this->initMap(level);

	return true;
}

bool GameMap::loadMap(const int& level)
{
	string fileName = StringUtils::format("map/map_%03d.tmx", level);
	TMXTiledMap* map = TMXTiledMap::create(fileName);
	m_map = map;
	float scale = 1 / Director::getInstance()->getContentScaleFactor();

	//GridPos
	TMXObjectGroup* group = map->getObjectGroup("TowerPos");
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
			if (t1 != t2 && pos.distanceSquared(t2->getPos())<=dis)
			{
				GridPosID.push_back(t2->ID);
			}
		}

		int around[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
		for (auto tid : GridPosID)
		{
			Rect rect = m_gridPos[tid]->getRect();
			if		(rect.containsPoint( Point(pos.x	, pos.y + h	)))around[North] = tid;
			else if (rect.containsPoint( Point(pos.x - w, pos.y + h	)))around[NorthWest] = tid;
			else if (rect.containsPoint( Point(pos.x - w, pos.y		)))around[West] = tid;
			else if (rect.containsPoint( Point(pos.x - w, pos.y - h	)))around[SouthWest] = tid;
			else if (rect.containsPoint( Point(pos.x	, pos.y - h	)))around[South] = tid;
			else if (rect.containsPoint( Point(pos.x + w, pos.y - h	)))around[SouthEast] = tid;
			else if (rect.containsPoint( Point(pos.x + w, pos.y		)))around[East] = tid;
			else if (rect.containsPoint( Point(pos.x + w, pos.y + h	)))around[NorthEast] = tid;
		}
		t1->setAroundGridPosID(around);
	}


	//MonsterPath
	group = map->getObjectGroup("Path");
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
	int waveCount= map->getProperty("WaveCount").asInt();
	std::stringstream ss;
	string propertyName;
	WaveList.clear();
	for (int i = 1; i <= waveCount; i++)
	{
		propertyName = StringUtils::format("Wave%03d", i);
		group = map->getObjectGroup(propertyName);
		CCASSERT(group != nullptr, string("propertyName :" + propertyName +" NOT found").c_str());

		Wave wave;
		wave.WaveTime = group->getProperty("waveTime").asInt();
		
		int momsterCount = group->getProperty("momsterCount").asInt();
		for (int j = 1; j <=momsterCount; j++)
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

	return true;
}

bool GameMap::initMap(int level)
{
	bool flag = true;

	do{
		SpellCardManager::getInstance()->LoadResource();
		TowerCardManager::getInstance()->LoadResource();

		std::vector<TowerCard> m_TowerCard;
		std::vector<SpellCard> m_SpellCard;
		auto towerMgr = TowerCardManager::getInstance();
		auto spellMgr = SpellCardManager::getInstance();

		vector<string> spellcardList;
		spellcardList.push_back("Damage_Add_I");
		spellcardList.push_back("Range_Add_I");
		spellcardList.push_back("ColdDown_Div_I");
		spellcardList.push_back("TargetCount_Add_I");
		spellcardList.push_back("CriticalChance_Add_I");
		spellcardList.push_back("MaxDamage_Add_I");
		spellcardList.push_back("CriticalMultiplier_Add_I");
		spellcardList.push_back("BoomRange_Add_I");

		SpellCard scard;
		for (int i = 0; i < 8; i++)
		{
			scard = *spellMgr->getSpellCard(spellcardList[i]);
			scard.gid = i;
			m_SpellCard.push_back(scard);
		}


		vector<string> towercardList;
		towercardList.push_back("card000");
		towercardList.push_back("card001");
		towercardList.push_back("card002");
		towercardList.push_back("card003");
		towercardList.push_back("card004");
		towercardList.push_back("card005");
		towercardList.push_back("card006");
		towercardList.push_back("card007");

		TowerCard tcard;
		for (int i = 0; i < 8; i++)
		{
			tcard = *towerMgr->getTowerCard(towercardList[i]);
			tcard.gid = i;
			m_TowerCard.push_back(tcard);
		}

		//玩家选择的卡牌
		Player* player = Player::getInstance();
		player->reset();
		player->setMoney(2000);
		player->setLife(20);
		player->setTowerCard(m_TowerCard);
		player->setSpellCard(m_SpellCard);

		//初始化所有Manager
		WaveManager::getInstance()->init();
		UnitManager::getInstance()->init(new TDUnitCreator());
		BehaviorManager::getInstance()->init();
		EffectManager::getInstance()->init();


		//载入资源
		vector<string> textureList;
		textureList.push_back("texture/scene_battle_000.plist");
		textureList.push_back("texture/UI/TowerSelectLayer.plist");
		textureList.push_back("texture/UI/TowerInfoLayer.plist");
		textureList.push_back("texture/UI/GameMapInfoLayer.plist");
		textureList.push_back("texture/effect/effect_000.plist");
		textureList.push_back("texture/Tower/Tower_000.plist");
		textureList.push_back("texture/Tower/Tower_001.plist");
		textureList.push_back("texture/Tower/Tower_006.plist");
		TextureManager::getInstance()->LoadResource(textureList);


		SkillManager::getInstance()->LoadResource();
		BehaviorManager::getInstance()->LoadResource();
		AnimateManager::getInstance()->LoadResource();
		ActorManager::getInstance()->LoadResource();
		WeaponManager::getInstance()->LoadResource();
		EffectManager::getInstance()->LoadResource();


		//vector<string> effectList;
		//SkillManager::getInstance()->LoadResource(effectList);

		//
		//vector<string> behaviorList;
		//behaviorList.push_back("BBuff_AddDamage_10");
		//behaviorList.push_back("BBuff_SubColdDown_0.5P");
		//BehaviorManager::getInstance()->LoadResource(behaviorList);
		//
		//vector<string> animateList;
		//animateList.push_back("blank");
		//animateList.push_back("error");
		//animateList.push_back("t001_stand");
		//animateList.push_back("t001_attack_beforing");
		//animateList.push_back("t001_skill_preparing");
		//animateList.push_back("t001_skill_beforing");
		//animateList.push_back("t001_skill_using");
		//animateList.push_back("t001_skill_aftering");
		//animateList.push_back("e001");
		//animateList.push_back("e002");
		//animateList.push_back("m001_move");
		//animateList.push_back("m001_death");
		//animateList.push_back("b001_move");
		//animateList.push_back("b002_move");
		//animateList.push_back("b003_move");
		//animateList.push_back("spellPos000");
		//animateList.push_back("spellPos001");
		//animateList.push_back("spellPos002");
		//animateList.push_back("spellPos003");
		//animateList.push_back("spellPos004");
		//animateList.push_back("spellPos005");
		//animateList.push_back("spellPos006");
		//animateList.push_back("spellPos007");
		//animateList.push_back("SpellTower_000");
		//animateList.push_back("SpellTower_001");
		//animateList.push_back("SpellTower_002");
		//animateList.push_back("SpellTower_003");
		//animateList.push_back("SpellTower_004");
		//animateList.push_back("SpellTower_005");
		//animateList.push_back("SpellTower_006");
		//animateList.push_back("SpellTower_007");
		//animateList.push_back("Tower_000");
		//animateList.push_back("Tower_001");
		//animateList.push_back("Tower_002");
		//animateList.push_back("Tower_003");
		//animateList.push_back("Tower_004");
		//animateList.push_back("Tower_005");
		//animateList.push_back("Tower_006");
		//animateList.push_back("Tower_007");
		//AnimateManager::getInstance()->LoadResource(animateList);


		//vector<string> actorList;
		//actorList.push_back("blank");
		//actorList.push_back("t001");
		//actorList.push_back("m001");
		//actorList.push_back("b001");
		//actorList.push_back("b002");
		//actorList.push_back("b003");
		//actorList.push_back("Tower_000");
		//actorList.push_back("Tower_001");
		//actorList.push_back("Tower_002");
		//actorList.push_back("Tower_003");
		//actorList.push_back("Tower_004");
		//actorList.push_back("Tower_005");
		//actorList.push_back("Tower_006");
		//actorList.push_back("Tower_007");
		//ActorManager::getInstance()->LoadResource(actorList);

		//vector<Name> weaponList;
		//weaponList.push_back("wTower001");
		//weaponList.push_back("wTower_000");
		//weaponList.push_back("wTower_001");
		//weaponList.push_back("wTower_002");
		//weaponList.push_back("wTower_003");
		//weaponList.push_back("wTower_004");
		//weaponList.push_back("wTower_005");
		//weaponList.push_back("wTower_006");
		//weaponList.push_back("wTower_007");
		//WeaponManager::getInstance()->LoadResource(weaponList);


		//vector<Name> spellTowerList;
		//SpellTowerManager::getInstance()->LoadResource(spellTowerList);


		//创建空白塔
		for (auto var : m_gridPos)
		{
			var->initTower();
		}

	} while (0);

	return flag;
}

TMXTiledMap*  GameMap::getMapLayer()
{
	return m_map;
}

GridPos* GameMap::getGridPos(int id)
{
	CCASSERT(id!=-1 && id < (int)m_gridPos.size(), "GridPosID NOT found");
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



void GameMap::update(float dt)
{
	UnitManager::getInstance()->update(dt);
	WaveManager::getInstance()->update(dt);
}

//
//bool GameMap::LoadMap(int level)
//{
//	FileUtils* fin = FileUtils::getInstance();
//
//	//string filePath = fin->getWritablePath();
//	string filePath = "";
//	string fileName = StringUtils::format("map/level_%d.map",level);
//	Data data = fin->getDataFromFile(filePath + fileName);
//	CCASSERT(!data.isNull(), string("map:" + filePath + fileName + " NOT exists").c_str());
//
//	byte* byt = data.getBytes();
//	int p = 0;
//
//	//MapSize
//	ReadData(m_mapSize.width, byt, p);
//	ReadData(m_mapSize.height, byt, p);
//
//	//GridPos
//	int GridPosCount, x, y;
//	ReadData(GridPosCount, byt, p);
//	p += GridPosCount * 8;//<----skip load tower pos
//	//for (int i = 0; i < GridPosCount; i++)
//	//{
//	//	ReadData(x, byt, p);
//	//	ReadData(y, byt, p);
//	//	GridPos.push_back(Point(x, y));
//	//}
//
//	//MonsterPath
//	int PathCount,PosCount;
//	ReadData(PathCount, byt, p);
//	//MonsterPath.resize(PathCount);
//	for (int i = 0; i < PathCount; i++){
//	//	//MapPath path;
//		int cccc;
//		ReadData(cccc, byt, p);
//		ReadData(PosCount, byt, p);
//		p += PosCount * 8;//<----skip load pos
//
//	//	for (int j = 0; j < PosCount; j++)
//	//	{
//	//		ReadData(x, byt, p);
//	//		ReadData(y, byt, p);
//
//	//		path.pos.push_back(Point(x, y));
//	//	}
//	//	MonsterPath.push_back(path);
//	}
//
//	//Wave
//	int waveCount,waveDataCount;
//	ReadData(waveCount, byt, p);
//	WaveList.resize(waveCount);
//
//	for (int i = 0; i < waveCount; i++)
//	{
//		Wave wave;
//		ReadData(wave.WaveTime, byt, p);
//		ReadData(waveDataCount, byt, p);
//		for (int j = 0; j <waveDataCount; j++)
//		{
//			WaveData data;
//			ReadData(data.PathID, byt, p);
//			ReadData(data.MonsterID, byt, p);
//			ReadData(data.NextDalay, byt, p);
//			wave.wavedata.push_back(data);
//		}
//		WaveList.push_back(wave);
//	}
//
//	//delete[] byt;
//	m_level = level;
//
//	return true;
//}
//
//template <typename T>
//void GameMap::ReadData(T& dest, const void* src, int& p){
//	memcpy(&dest, (char*)src+p, sizeof(dest));
//	p += sizeof(dest);
//}




