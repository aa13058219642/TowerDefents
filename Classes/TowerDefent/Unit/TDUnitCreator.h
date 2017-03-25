#pragma once
#include "stdfax.h"
#include "TowerDefentShare.h"



class TDUnitCreator : public cocosgalaxy::UnitCreator
{
public:
	TDUnitCreator();
	~TDUnitCreator();

	virtual CGameData* Create(string className, string typeName = "");
	virtual CGameData* Create(int classHash, string typeName = "");
};
