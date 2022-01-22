#pragma once
#include "Renderer.h"
#include "Player.h"

typedef struct objPellete
{
	COORD Pos;
	struct _norm2DVecDir
	{
		float x, y; // x = cos(theta) , y = sin(theta)
	} Direction;
	float Speed;
	char chr;
	int Damage;
	int Enabled;
} Pellete;

void RenderPellete(Pellete* p);
void UpdatePellete(Pellete* p,COORD playerPos);