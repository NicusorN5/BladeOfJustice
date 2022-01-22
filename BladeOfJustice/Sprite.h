#pragma once
#include "Renderer.h"

typedef struct dataSprite
{
	DWORD Spr[32][32];
	size_t X, Y;
} Sprite;

DWORD CreateSpriteFromFile(Sprite** sprite, char* file, COORD expected_dimentions);

DWORD CreateEmptySprite(Sprite** sprite);

void RenderSprite(Sprite* sprite,COORD pos);

void DestroySprite(Sprite* sprite);

void DebugPrintSprite(Sprite* sprite);