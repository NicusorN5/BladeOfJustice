#pragma once
#include <stdint.h>

extern struct GameSection MainMenu;

void MainMenu_Input(int* input,size_t l);

void MainMenu_Update(float dt);

void MainMenu_Draw(float dt);