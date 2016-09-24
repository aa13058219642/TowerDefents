#pragma once
#include "ResourceLoader.h"
#include "SpellCard.h"

class SpellCardManager :public ResourceLoader
{
public:
	//µ¥ÀýÄ£Ê½
	static SpellCardManager* getInstance();
	~SpellCardManager();

	virtual void LoadResource();
	virtual void LoadResource(const vector<Name>& resNameList);
	virtual void FreeAllResource();
	virtual void FreeResource(const vector<Name>& resName);

	const SpellCard* getSpellCard(int id);
	const SpellCard* getSpellCard(Name name);


private:
	SpellCardManager();
	static SpellCardManager* p_myinstance;

	map<Name, SpellCard*> m_spellTower;

};



