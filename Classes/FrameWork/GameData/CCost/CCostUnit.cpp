#include "CCostUnit.h"
#include "Unit.h"

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


bool CCostUnit::isCanPay(Unit* parent)
{
	if (parent->HP >= HP &&
		parent->MP >= MP &&
		parent->AP >= AP &&
		parent->Speed >= Speed)
	{
		return true;
	}
	return false;
}

void CCostUnit::payCost(Unit* parent)
{
	parent->HP.add(HP, true);
	parent->MP.add(MP, true);
	parent->AP.add(AP, true);
	parent->Speed.add(Speed, true);
}










