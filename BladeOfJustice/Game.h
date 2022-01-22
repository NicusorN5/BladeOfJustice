#pragma once
#include "Cutscene.h"
#include "Level1.h"
#include "Fight1.h"

extern int GameLevel;

DWORD InitializeNewGame();

void Game_Input(DWORD key);

void Game_Draw(float dt);

void Game_Unload();

void SaveGame(int slot);