#pragma once
#include <stdint.h>
#include "Main.h"
#include "Sprite.h"

DWORD MainMenu_LoadContent();

void MainMenu_Input(DWORD key);

void MainMenu_Update(float dt);

void MainMenu_Draw(float dt);

void MainMenu_Unload();