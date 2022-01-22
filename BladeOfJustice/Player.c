#include "Player.h"

Player MainPlayer;

void InitializePlayerDefaultValues(Player* plr)
{
	plr->AromurID = 0;
	plr->WeaponID = 1;
	plr->WeaponID = 2;
	plr->numPotions = 3;
}

void LoadPlayerState(int saveId)
{
	char file[20];

	sprintf(file, "savefile%i.save");

	FILE* savefile = fopen(file, "r");
	fscanf(savefile, "%i", &GameLevel);
	fclose(savefile);

	GameSection = gamepart_NewGame;
}

void SavePlayerState(int saveId)
{
	char file[20];
	FILE* savefile = open(file, "w+");

	fprintf(savefile, "%i", GameLevel);
	fclose(savefile);
}
