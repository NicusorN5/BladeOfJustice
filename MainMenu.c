#include "MainMenu.h"
#include "KeyMacros.h"
#include "Main.h"

void MainMenu_Input(int* input, size_t l)
{
	for (size_t i = 0; i < l; i++)
	{
		switch (input[i])
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
}

void MainMenu_Update(float dt)
{
}

void MainMenu_Draw(float dt)
{

}