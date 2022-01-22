#pragma once
#include "Globals.h"

typedef struct _dataPlayer
{
	int Health;
	int WeaponID;
	int AromurID;
	int numPotions;
} Player;

extern Player MainPlayer;

void InitializePlayerDefaultValues(Player *plr);
void LoadPlayerState(int saveId);
void SavePlayerState(int saveId);