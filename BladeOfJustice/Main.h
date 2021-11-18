#pragma once
#include "MainMenu.h"
#include "Input.h"
#include "Renderer.h"

extern int GameRunning;

enum GamePart
{
	gamepart_MainMenu = 0,
	gamepart_NewGame = 1,
	gamepart_LoadGame = 2,
	gamepart_Settings = 3,
	gamepart_World = 4,
	gamepart_Inventory = 5,
	gamepart_Battle = 6,
	gamepart_Cutscene = 7,
};

int Clamp(int a, int t, int b);

int main();