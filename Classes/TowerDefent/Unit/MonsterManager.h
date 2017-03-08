#pragma once
#include "ResourceLoader.h"
#include "Monster.h"

class MonsterManager :public ResourceLoader
{
public:
	//单例模式
	static MonsterManager* getInstance();
	~MonsterManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);


	Monster* CreateMonster(string monsterName);
	Monster* CreateMonster(int monsterID);

private:
	MonsterManager();
	static MonsterManager* p_myinstance;

	std::map<Name, Monster*> monsterslist;

};



