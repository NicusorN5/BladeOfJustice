#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#define GAME_SCREEN_X 800
#define GAME_SCREEN_Y 600

extern HWND ConsoleWindow;
extern DWORD OriginalColor;
extern HANDLE ConsoleHandle;
extern CHAR_INFO Screen[GAME_SCREEN_Y][GAME_SCREEN_X]; // X and Y's are swapped! I didn't know this for years, Jesus Christ dude
//extern WORD Screen[200][200];

void PrepareConsoleForDrawing();

void PrintScreen();

DWORD GetConsoleTextAttribute(HANDLE hCon);

void ClearScreen();

void SetScreenPixel(WORD color, COORD pos);

void SetScreenCharacter(WORD color, COORD pos, char chr);

void WriteScreen(WORD color, COORD pos, char* str);