#pragma once
#include "stdfax.h"

//MessageCenter///////////////////////////////////////////////////////////////////////////
#define Message_TowerSelectLayer "Message_TowerSelectLayer"
#define Message_TowerInfoLayer "Message_TowerInfoLayer"
typedef ValueMap NotificationMsg;

enum MsgCMD : int{
	unknow,
	TowerSelectLayer_ClickEmptyGridPos,
	TowerSelectLayer_ClickTowerGridPos,
	TowerSelectLayer_ClickSpellEmptyGridPos,
	TowerSelectLayer_ClickSpellTowerGridPos
};










