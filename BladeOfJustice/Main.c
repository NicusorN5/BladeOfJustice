#include "Main.h"

DWORD WINAPI DoGameInput(void * data)
{
	while (GameRunning)
	{
		switch (GameSection)
		{
			case gamepart_MainMenu:
			{
				MainMenu_Input(LastKey);
				break;
			}
			case gamepart_NewGame:
			{
				Game_Input(LastKey);
				break;
			}
			case gamepart_Credits:
			{
				Credits_Input(LastKey);
				break;
			}
			default:
				break;
		}
		//input cleanup
		LastKey = 0;
		Sleep(33);
	}

	return 0;
}

clock_t Time1,Time2;

DWORD WINAPI DoGameDrawing(void* data)
{
	while (GameRunning)
	{
		Time1 = clock();
		ClearScreenWithColor(ClearColor);

		switch (GameSection)
		{
			case gamepart_MainMenu:
			{
				MainMenu_Draw(Time2);
				break;
			}
			case gamepart_NewGame:
			{
				Game_Draw(Time2);
				break;
			}
			case gamepart_LoadGame:
			{
				break;
			}
			case gamepart_Settings:
			{
				break;
			}
			case gamepart_Credits:
			{
				Credits_Draw(); //no need for a dt value.
				break;
			}
			default: 
				break;

		}

		PrintScreen();
		Time2 = (float)((clock() - Time1) / CLOCKS_PER_SEC);
		//Sleep(33);
	}
	return 0;
}

int main()
{
	wchar_t file[MAX_PATH];
	GetModuleFileNameW(NULL, file, MAX_PATH);
	PathCchRemoveFileSpec(file, MAX_PATH);
	SetCurrentDirectoryW(file);

	GameSection = gamepart_MainMenu;

	PrepareConsoleForDrawing();
	PrepareInput();

	GameRunning = 1;

	SetConsoleTextAttribute(ConsoleHandle, 0x01);

	if (MainMenu_LoadContent() != S_OK)
	{
		MessageBoxA(NULL, "Failed to load main menu sprite files!", "Loading fail!", MB_OK | MB_ICONERROR);
		exit(-3);
	}
	if (InitializeNewGame() != S_OK)
	{
		MessageBoxA(NULL, "Failed to load the intro cutscene! Files are missing!", "Level loading failiure!", MB_OK | MB_ICONERROR);
		exit(-4);
	}

	HANDLE DrawThread = CreateThread(NULL, 1024, DoGameDrawing, NULL, 0, NULL);
	if (DrawThread == NULL)
	{
		MessageBoxA(NULL, "Failed to create drawing thread!", "Cannot start game", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	HANDLE InputThread = CreateThread(NULL, 1024, DoGameInput, NULL, 0, NULL);
	if (InputThread == NULL)
	{
		MessageBoxA(NULL, "Failed to create input thread!", "Cannot start game", MB_OK | MB_ICONERROR);
		exit(-2);
	}

	CloseHandle(DrawThread);
	CloseHandle(InputThread);

	MSG m;
	while (GameRunning)
	{
		PeekMessageA(&m, NULL, 0, 0,PM_REMOVE);
	}
	//cleanup

	ClearScreen();
	PrintScreen();

	MainMenu_Unload();

	return 0;
}