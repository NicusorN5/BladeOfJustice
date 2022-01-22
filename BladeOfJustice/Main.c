#include "Renderer.h"

int main()
{
	GameError e = Renderer_Initialize();
	if(e != gerr_Ok)
	{
		DWORD err = GetLastError();
		MessageBoxA(NULL, "Oops! Initialization fail!", "Oh no!", MB_ICONERROR | MB_OK);
	}

	/*
	for(size_t i = 0; i < 800; i++)
	{
		for(size_t j = 0; j < 600; j++)
		{ 
			Point p = { i,j };
			Renderer_SetPixel(&p, (rand() % 17) * 0x10);
		}
	}
	*/
	Renderer_SetPixel(500, 0, 0x10);
	Renderer_SetPixel(600, 0, 0x20);
	Renderer_SetPixel(800, 0, 0x30);
	Renderer_Draw();
}