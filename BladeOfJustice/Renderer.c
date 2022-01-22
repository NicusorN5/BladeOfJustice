#include "Renderer.h"

HWND ConsoleWindow = NULL;
DWORD OriginalColor = 0x0F;
HANDLE ConsoleHandle = NULL;
HANDLE ConsoleHandleInp = NULL;

CHAR_INFO Screen[GAME_SCREEN_Y][GAME_SCREEN_X];

void PrepareConsoleForDrawing()
{
	//get handles
	ConsoleWindow = GetConsoleWindow();
	OriginalColor = GetConsoleTextAttribute(ConsoleWindow);
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // stdout / cout
	ConsoleHandleInp = GetStdHandle(STD_INPUT_HANDLE); //stdin / cin

	//set window title and visibility
	SetWindowTextA(ConsoleWindow, "Blade of justice");

	SetConsoleDisplayMode(ConsoleHandle, CONSOLE_FULLSCREEN_MODE, NULL);
	SetConsoleDisplayMode(ConsoleHandleInp, CONSOLE_FULLSCREEN_MODE, NULL);

	//set font size
	CONSOLE_FONT_INFOEX consoleFont;
	memset(&consoleFont, 0, sizeof(CONSOLE_FONT_INFOEX));
	consoleFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	consoleFont.dwFontSize.X = 8;
	consoleFont.dwFontSize.Y = 8;
	consoleFont.FontFamily = FF_DONTCARE;
	consoleFont.FontWeight = FW_NORMAL;
	wcscpy(consoleFont.FaceName, L"Raster Fonts");
	SetCurrentConsoleFontEx(ConsoleHandle, FALSE, &consoleFont);
	SetCurrentConsoleFontEx(ConsoleHandleInp, FALSE, &consoleFont);

	//remove scrollbar
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(ConsoleHandle,&csbi);

	COORD ns; //LNT1006 : VS2019 is drunk 
	ns.X = csbi.srWindow.Right - csbi.srWindow.Left + 1; // columns
	ns.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // rows

	SetConsoleScreenBufferSize(ConsoleHandle, ns);

	//remove cursor
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(ConsoleHandle, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(ConsoleHandle, &cci);

	for (int i = 0; i < GAME_SCREEN_Y; i++)
	{
		for (int j = 0; j < GAME_SCREEN_X; j++)
		{
			CHAR_INFO ci = { ' ',0x01 };
			Screen[i][j] = ci;
		}
	}
}

DWORD GetConsoleTextAttribute(HANDLE hCon)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	return csbi.wAttributes;
}


void PrintScreen()
{
	COORD top_left = { 0,0 };
	COORD screenSize = { GAME_SCREEN_X,GAME_SCREEN_Y };
	
	SMALL_RECT r;
	memset(&r, 0, sizeof(SMALL_RECT));

	RECT monitorResolution;
	GetWindowRect(GetDesktopWindow(), &monitorResolution);

	r.Bottom = monitorResolution.bottom;
	r.Right = monitorResolution.right;

#pragma warning(push)
#pragma warning(disable: 4047)
#pragma warning(disable: 6385)
	WriteConsoleOutputA(ConsoleHandle, Screen, screenSize, top_left, &r);
#pragma warning(pop)
}

void ClearScreen()
{
	for (int i = 0; i < GAME_SCREEN_Y; i++)
	{
		for (int j = 0; j < GAME_SCREEN_X; j++)
		{
			CHAR_INFO ci = { ' ',0x01 };
			Screen[i][j] = ci;
		}
	}
}

void ClearScreenWithColor(WORD color)
{
	for (int i = 0; i < GAME_SCREEN_Y; i++)
	{
		for (int j = 0; j < GAME_SCREEN_X; j++)
		{
			CHAR_INFO ci = { ' ',color };
			Screen[i][j] = ci;
		}
	}
}

void SetScreenPixel(WORD color,COORD pos)
{
	Screen[pos.Y][pos.X].Attributes = color;
}
void SetScreenCharacter(WORD color, COORD pos, char chr)
{
	if (pos.X < 800 && pos.Y < 600 && pos.X >= 0 && pos.Y >= 0) 
	{
		Screen[pos.Y][pos.X].Attributes = color;
		Screen[pos.Y][pos.X].Char.AsciiChar = chr;
	}
}

void WriteScreen(WORD color, COORD pos, char* str)
{
	size_t l = strlen(str);
	for (unsigned i = 0; i < l; i++)
	{
		Screen[pos.Y][pos.X+i].Attributes = color;
		Screen[pos.Y][pos.X+i].Char.AsciiChar = str[i];
	}
}
