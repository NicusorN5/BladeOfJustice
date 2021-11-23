#pragma once
#include "Renderer.h"

struct Sprite
{
	DWORD Spr[32][32];
	size_t X, Y;
};

DWORD CreateSpriteFromFile(struct Sprite** sprite, char* file, COORD expected_dimentions);

DWORD CreateEmptySprite(struct Sprite** sprite);

void RenderSprite(struct Sprite* sprite,COORD pos);

void DestroySprite(struct Sprite* sprite);

void DebugPrintSprite(struct Sprite* sprite);