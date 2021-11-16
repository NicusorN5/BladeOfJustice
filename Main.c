#include "Main.h"

int GameRunning = 1;

int Clamp(int a,int t, int b)
{
	if (t >= b) return b;
	if (t <= a) return a;
	else return t;
}

DWORD WINAPI DoGameInput(void * data)
{
	enum GamePart GameSection = (enum GamePart)*((int*)data);
	while (GameRunning)
	{
		if (_kbhit())
		{
			int chr[] = { _getch(),_getch(),_getch(),_getch() }; //For arrow keys we need 2 function calls.
			switch (GameSection)
			{
				case gamepart_MainMenu:
				{
					MainMenu_Input(chr, 4);
					break;
				}
				default: break;
			}
		}
	}
	return 0;
}
DWORD WINAPI DoGameDrawing(void* data)
{
	enum GamePart GameSection = (enum GamePart)*((int*)data);

	while (GameRunning)
	{
		ClearScreen();
		for (int x = 0; x < GAME_SCREEN_X; x++)
		{
			for (int y = 0; y < GAME_SCREEN_Y; y++)
			{
				COORD p = { x,y };
				SetScreenPixel((rand() % 16) * 0xA + 1, p);
			}
		}
		PrintScreen();
		//Sleep(33);
	}
	return 0;
}

int main()
{
	enum GamePart GameSection = gamepart_MainMenu;

	PrepareConsoleForDrawing();

	GameRunning = 1;

	SetConsoleTextAttribute(ConsoleHandle, 0x01);

	HANDLE DrawThread = CreateThread(NULL, 1024, DoGameDrawing, &GameSection, 0, NULL);
	if (DrawThread == NULL)
	{
		MessageBoxA(NULL, "Failed to create drawing thread!", "Cannot start game", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	WaitForSingleObject(DrawThread, INFINITE);

	return 0;

}