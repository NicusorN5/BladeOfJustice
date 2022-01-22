#pragma once
#include "Libs.h"

extern CHAR_INFO Screen[600][800];
extern HANDLE StdHandle;
extern HWND ConsoleWindow;

typedef enum _gameErrorCode
{
	gerr_Ok,
	gerr_InitFail,
	gerr_OutOfMem,
	gerr_FileNotFound,
	gerr_Unknown
} GameError;

GameError Renderer_Initialize();

void Renderer_SetPixel(uint8_t x,uint8_t y,WORD color);

void Renderer_Draw();