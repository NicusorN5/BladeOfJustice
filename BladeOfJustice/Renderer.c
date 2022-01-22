#include "Renderer.h"

CHAR_INFO Screen[600][800];
HANDLE StdHandle = INVALID_HANDLE_VALUE;
HWND ConsoleWindow = NULL;

GameError Renderer_Initialize()
{
	ConsoleWindow = GetConsoleWindow();
	if(ConsoleWindow == NULL)
		return gerr_InitFail;

	StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(StdHandle == INVALID_HANDLE_VALUE)
		return gerr_InitFail;

	BOOL f = SetConsoleTitleA("Blade of Justice");
	if(!f) return gerr_InitFail;

	CONSOLE_FONT_INFOEX font;
	memset(&font, 0, sizeof(CONSOLE_FONT_INFOEX));
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize.X = 1;
	font.dwFontSize.Y = 1;
	font.FontWeight = FW_NORMAL;
	font.FontFamily = FF_DONTCARE;
	lstrcpyW(font.FaceName, L"Raster Fonts");

	f = SetCurrentConsoleFontEx(StdHandle, TRUE, &font);
	if(!f) return gerr_InitFail;

	COORD ScreenSize = { 800,600 };
	f = SetConsoleScreenBufferSize(StdHandle, ScreenSize);
	if(!f) return gerr_InitFail;

	f = SetConsoleDisplayMode(StdHandle, CONSOLE_FULLSCREEN_MODE, NULL);
	if(!f) return gerr_InitFail;
	
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = 1;
	f = SetConsoleCursorInfo(StdHandle, &cursor);
	if(!f) return gerr_InitFail;

	f = ShowScrollBar(ConsoleWindow, SB_BOTH, FALSE);
	if(!f) return gerr_InitFail;

	DWORD ConsoleMode = 0;
	f = GetConsoleMode(StdHandle, &ConsoleMode);
	if(!f) return gerr_InitFail;

	f = SetConsoleMode(StdHandle, ConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	if(!f) return gerr_InitFail;

	for(size_t i = 0; i < 800; i++)
	{
		for(size_t j = 0; j < 600; j++)
		{
			CHAR_INFO chrInfo;
			chrInfo.Char.AsciiChar = ' ';
			chrInfo.Attributes = 0;
			Screen[j][i] = chrInfo;
		}
	}

	return gerr_Ok;
}

void Renderer_SetPixel(uint8_t x,uint8_t y,WORD color)
{
	Screen[y][x].Attributes = color;
}

void Renderer_Draw()
{
	COORD BufferSize = { 600,800 }, ZeroCoord = {0,0};
	SMALL_RECT writeRegion;
	memset(&writeRegion, 0, sizeof(SMALL_RECT));
	writeRegion.Right = 800;
	writeRegion.Bottom = 600;
#pragma warning(push)
#pragma warning(disable: 4047)
#pragma warning(disable: 6385)
	WriteConsoleOutputA(StdHandle, Screen, BufferSize, ZeroCoord,&writeRegion);
#pragma warning(pop)
}
