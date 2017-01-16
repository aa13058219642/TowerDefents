#include "CCostPlayer.h"
#include "Player.h"
using namespace cocosgalaxy;

CCostPlayer::CCostPlayer()
{

}


CCostPlayer::~CCostPlayer()
{

}

bool CCostPlayer::isCanPay(CGameData* gamedata)
{
	Player* player = static_cast<Player*>(gamedata);

	if (player->getMoney() >= this->money)
	{
		return true;
	}

	return false;
}

void CCostPlayer::payCost(CGameData* gamedata)
{
	Player* player = static_cast<Player*>(gamedata);
	player->addMoney(-this->money);
}



