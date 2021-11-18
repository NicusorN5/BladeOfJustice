#include "MainMenu.h"

int SelectionMenuIndex = 0;

void MainMenu_Input(char key)
{
	switch (key)
	{
		case KEY_DOWN:
		{
			break;
		}
		case KEY_ENTER:
		{
			break;
		}
		case KEY_ESC:
		{
			GameRunning = 0;
			return;
		}
	}
}

void MainMenu_Update(float dt)
{
}

void MainMenu_Draw(float dt)
{
	COORD p1 = { 0,0 };
	SetScreenCharacter(0x0F, p1, '>');

	COORD p2 = { 1,0 };
	WriteScreen(0x3F, p2, "New game");
}