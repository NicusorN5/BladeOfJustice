#pragma once
/*
* 
*	BLADE OF JUSTICE
*	(Author: Tugui Nicolae (Codebase developing time: ~7 Nov 2021 -> 22 Jan 2022)
* 
*/

#include "MainMenu.h"
#include "Input.h"
#include "Renderer.h"
#include "Globals.h"
#include "Credits.h"
#include "Game.h"

DWORD WINAPI DoGameInput(void* data);

DWORD WINAPI DoGameDrawing(void* data);

int main();

// tbh ma simt oribil ca am irosit timpul pe constuit protitipuri (am incercat sa evit cat de mult posibil API-rile din consola (consoleapi3.h))
// am stat mai mult sa fac un joc care randeaza AVI-uri.