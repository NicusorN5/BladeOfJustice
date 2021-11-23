#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <PathCch.h>
#include <math.h>

#pragma comment(lib,"Pathcch.lib")
#pragma comment(lib,"Winmm.lib")

enum GamePart
{
	//main menu related (depth 0)
	gamepart_MainMenu = 0,
	gamepart_NewGame = 1,
	gamepart_LoadGame = 2,
	gamepart_Settings = 3,
	gamepart_Credits = 4,

	//gameplay related (depth 1)
	gamepart_Cutscene = 5,
	gamepart_World = 6,
	gamepart_Inventory = 7,
	gamepart_Battle = 8,
};

extern int GameRunning;

extern enum GamePart GameSection;

extern DWORD ClearColor;

extern int GameLevel;