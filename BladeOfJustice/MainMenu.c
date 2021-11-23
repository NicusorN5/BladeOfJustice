#include "MainMenu.h"

int SelectionMenuIndex = 0;

struct Sprite* Logo1, *Logo2, *Logo3;

DWORD MainMenu_LoadContent()
{
	COORD def_coords = { 32,7 };
	DWORD errc;
	errc = CreateSpriteFromFile(&Logo1, "Sprites//Logo1.bojimg", def_coords); if (errc != S_OK) return errc;
	errc = CreateSpriteFromFile(&Logo2, "Sprites//Logo2.bojimg", def_coords); if (errc != S_OK) return errc;
	errc = CreateSpriteFromFile(&Logo3, "Sprites//Logo3.bojimg", def_coords); if (errc != S_OK) return errc;
	return S_OK;
}

void MainMenu_Input(DWORD key)
{
	switch (key)
	{
		case VK_DOWN:
		{
			SelectionMenuIndex += 1;
			break;
		}
		case VK_UP:
		{
			SelectionMenuIndex -= 1;
			break;
		}
		case VK_RETURN:
		{
			switch (SelectionMenuIndex)
			{
				case 0:
				{
					GameSection = gamepart_NewGame;
					break;
				}
				case 1:
				{
					GameSection = gamepart_LoadGame;
					break;
				}
				case 2:
				{
					GameSection = gamepart_Settings;
					break;
				}
				case 3:
				{
					GameSection = gamepart_Credits;
					break;
				}
				case 4:
				{
					GameRunning = 0;
					break;
				}
				default: 
					break;
			}
			break;
		}
		case VK_ESCAPE:
		{
			GameRunning = 0;
			return;
		}
	}
	SelectionMenuIndex = Clamp(0, SelectionMenuIndex, 4);
}

void MainMenu_Update(float dt)
{
}

void MainMenu_Draw(float dt)
{

	COORD arrowpos = {0,10 + 2 * SelectionMenuIndex};
	SetScreenCharacter(0x3F, arrowpos, '>');

	COORD p[] = { {0,0}, { 1,10 },{1,12},{1,14},{1,16},{1,18},{32,0},{64,0},{32,3 } }; //C doesn't have operator overloading bruh

	RenderSprite(Logo1, p[0]);
	RenderSprite(Logo2, p[6]);
	RenderSprite(Logo3, p[7]);

	WriteScreen(0x1C, p[8], "B  l  a  d  e    o  f   J  u  s  t  i  c  e");

	WriteScreen(0x1F, p[1], "New game");
	WriteScreen(0x1f, p[2], "Load game");
	WriteScreen(0x1f, p[3], "Settings");
	WriteScreen(0x1f, p[4], "Credits");
	WriteScreen(0x1f, p[5], "Exit");
}

void MainMenu_Unload()
{
	DestroySprite(Logo1);
}
