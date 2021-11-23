#include "Game.h"

DWORD InitializeNewGame()
{
	DWORD r = Cutscene1_Load(); if (r != S_OK) return r;
}

void Game_Input(DWORD key)
{
	switch (GameLevel)
	{
		default: break;
	}
}

void Game_Draw(float dt)
{
	switch (GameLevel)
	{
		case 0:
		{
			Cutscene1_Draw(dt);
			break;
		}
		case 1:
		{
			GameSection = gamepart_MainMenu;
			break;
		}
		default: break;
	}
}

void Game_Unload()
{
	Cutscene1_Destroy();
}

void SaveGame(int slot)
{

}
