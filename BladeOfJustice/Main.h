#pragma once
/*
* 
*	BLADE OF JUSTICE
*	(Author: Tugui Nicolae (Codebase developing time: ~7 Nov 2021 -> ?? ?? 2022)
* 
*/
#include "MainMenu.h"
#include "Input.h"
#include "Renderer.h"
#include "Globals.h"
#include "Credits.h"
#include "Game.h"

int Clamp(int a, int t, int b);

DWORD WINAPI DoGameInput(void* data);

DWORD WINAPI DoGameDrawing(void* data);

int main();