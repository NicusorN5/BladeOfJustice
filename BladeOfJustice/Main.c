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
		switch (GameSection)
		{
			case gamepart_MainMenu:
			{
				MainMenu_Input(LastKey);
				break;
			}
			default:
				break;
		}
	}
	return 0;
}

time_t Time1, Time2;


DWORD WINAPI DoGameDrawing(void* data)
{
	enum GamePart GameSection = (enum GamePart)*((int*)data);

	while (GameRunning)
	{

		Time1 = time(NULL);
		ClearScreen();

		switch (GameSection)
		{
			case gamepart_MainMenu:
			{
				MainMenu_Draw((float) (Time2 - Time1) / 1000 );
				break;
			}
			default: 
				break;

		}

		PrintScreen();
		Time2 = time(NULL);
		//Sleep(33);
	}
	return 0;
}

int main()
{
	enum GamePart GameSection = gamepart_MainMenu;

	PrepareConsoleForDrawing();
	PrepareInput();

	GameRunning = 1;

	SetConsoleTextAttribute(ConsoleHandle, 0x01);

	HANDLE DrawThread = CreateThread(NULL, 1024, DoGameDrawing, &GameSection, 0, NULL);
	if (DrawThread == NULL)
	{
		MessageBoxA(NULL, "Failed to create drawing thread!", "Cannot start game", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	HANDLE InputThread = CreateThread(NULL, 1024, DoGameInput, &GameSection, 0, NULL);
	if (InputThread == NULL)
	{
		MessageBoxA(NULL, "Failed to create input thread!", "Cannot start game", MB_OK | MB_ICONERROR);
		exit(-2);
	}

	CloseHandle(DrawThread);
	CloseHandle(InputThread);

	while (GetMessageA(NULL, NULL, 0, 0) && GameRunning)
	{

	}

	return 0;

}