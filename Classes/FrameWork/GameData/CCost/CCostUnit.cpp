#include "CCostUnit.h"
#include "CUnit.h"
using namespace cocosgalaxy;

CCostUnit::CCostUnit()
{
	HP = 0;
	MP = 0;
	AP = 0;
	Speed = 0;
}




CCostUnit::~CCostUnit()
{

}


bool CCostUnit::isCanPay(CGameData* gamedata)
{
	CUnit* parent = static_cast<CUnit*>(gamedata);

	if (parent->HP >= HP &&
		parent->MP >= MP &&
		parent->AP >= AP &&
		parent->Speed >= Speed)
	{
		return true;
	}
	return false;
}

void CCostUnit::payCost(CGameData* gamedata)
{
	CUnit* parent = static_cast<CUnit*>(gamedata);

	parent->HP < HP.getValue() ? parent->HP = 0 : parent->HP -= HP.getValue();
	parent->MP < MP.getValue() ? parent->MP = 0 : parent->MP -= MP.getValue();
	parent->AP < AP.getValue() ? parent->AP = 0 : parent->AP -= AP.getValue();
	parent->Speed < Speed.getValue() ? parent->Speed = 0 : parent->Speed -= Speed.getValue();
}










