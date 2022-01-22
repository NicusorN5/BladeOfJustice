#include "Sprite.h"

DWORD CreateSpriteFromFile(Sprite** sprite, char* file,COORD expected_dimentions)
{	
	*sprite = NULL;

	//swap coordinates
	SHORT alt;
	alt = expected_dimentions.X;
	expected_dimentions.X = expected_dimentions.Y;
	expected_dimentions.Y = alt;

	FILE* fptr = fopen(file, "r");
	if (fptr == NULL) return ERROR_FILE_NOT_FOUND;
	else
	{
		*sprite = malloc(sizeof(Sprite));

		if (*sprite == NULL)
		{
			return ERROR_OUTOFMEMORY;
		}
		(*sprite)->X = expected_dimentions.X;
		(*sprite)->Y = expected_dimentions.Y;

		for (int i = 0; i < expected_dimentions.X; i++)
		{
			for (int j = 0; j < expected_dimentions.Y; j++)
			{
				int r = fscanf(fptr, "%i", &(*sprite)->Spr[i][j]);
				int d = (*sprite)->Spr[i][j];
				if (r != 1)
				{
					return E_FAIL;
				}
			}
		}

		fclose(fptr);
		return S_OK;
	}
}

DWORD CreateEmptySprite(Sprite** sprite)
{
	*sprite = malloc(sizeof(Sprite));

	if (*sprite == NULL)
	{
		return E_OUTOFMEMORY;
	}

	memset(sprite, 17, sizeof(Sprite));
	return S_OK;
}

void RenderSprite(Sprite* sprite,COORD pos)
{
	for (unsigned i = 0; i < sprite->X; i++)
	{
		for (unsigned j = 0; j < sprite->Y; j++)
		{
			COORD npos = { pos.X + j ,pos.Y + i };
			if (sprite->Spr[i][j] >= 0 && sprite->Spr[i][j] <= 16)
			{
				SetScreenPixel(sprite->Spr[i][j] * 0x10, npos);
			}
		}
	}
}

void DestroySprite(Sprite* sprite)
{
	free(sprite);
}

void DebugPrintSprite(Sprite* sprite)
{
	puts("SPRITE DEBUG PRINT:");
	for (unsigned i = 0; i < sprite->X; i++)
	{
		for (unsigned j = 0; j < sprite->Y; j++)
		{
			printf("%i ", sprite->Spr[i][j]);
		}
		puts("");
	}
}
