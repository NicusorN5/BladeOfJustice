#include "Credits.h"

void Credits_Input(DWORD key)
{
	if (key == VK_ESCAPE)
	{
		GameSection = gamepart_MainMenu;
	}
}

void Credits_Draw()
{
	COORD p[] = { {50,1},{1,3},{2,5} , {10,5}, {2,7} ,{14,7}, {1,50 },{7,50} };
	WriteScreen(0x01, p[0], "Blade of justice");
	WriteScreen(0x02, p[1], "Credits:");
	WriteScreen(0x0F, p[2], "Author: ");
	WriteScreen(0x04, p[3], "Tugui Nicolae");
	WriteScreen(0x0F, p[4], "Build date: " );
	WriteScreen(0x01, p[5], __DATE__);
	WriteScreen(0x04, p[6],"[ESC]");
	WriteScreen(0x0F, p[7],"Return to main menu");
}
