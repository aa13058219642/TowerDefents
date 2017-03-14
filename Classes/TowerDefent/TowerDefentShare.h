#pragma once
#include "stdfax.h"

//MessageCenter///////////////////////////////////////////////////////////////////////////
#define Message_TowerSelectLayer "Message_TowerSelectLayer"
#define Message_TowerInfoLayer "Message_TowerInfoLayer"
#define Message_GameInfoLayer "Message_GameInfoLayer"
#define Message_GameMap "Message_GameMap"
#define Message_PrepareScene "Message_PrepareScene"

#define Message_Player "Message_Player"
#define Message_Global "Message_Global"


typedef ValueMap NotificationMsg;

enum MsgCMD : int{
	unknow,
	TowerSelectLayer_ClickEmptyGridPos,
	TowerSelectLayer_ClickTowerGridPos,
	TowerSelectLayer_ClickSpellEmptyGridPos,
	TowerSelectLayer_ClickSpellTowerGridPos,

	TowerInfoLayer_UpdateMoney,
	TowerInfoLayer_UpdateLife,

	Player_UpdateMoney,

};










