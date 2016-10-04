#pragma once
#include "ResourceLoader.h"
#include "TowerCard.h"

class TowerCardManager :public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static TowerCardManager* getInstance();
	~TowerCardManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	const TowerCard* getTowerCard(int id);
	const TowerCard* getTowerCard(Name name);


private:
	TowerCardManager();
	static TowerCardManager* p_myinstance;

	map<Name, TowerCard*> m_card;

};



