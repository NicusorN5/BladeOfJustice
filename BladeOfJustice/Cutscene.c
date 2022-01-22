#include "Cutscene.h"

DWORD CreateAnimation(struct Animation** animation,Sprite* affected_sprite, COORD initial_pos, COORD final_pos, int frames)
{
	*animation = NULL;

	*animation = malloc(sizeof(struct Animation));
	struct Animation* anim = *animation;
	if (anim == NULL) return E_OUTOFMEMORY;
	
	anim->frames = frames;
	anim->initial_pos = initial_pos;
	anim->sprite = affected_sprite;
	anim->to_pos = initial_pos;

	return S_OK;
}

DWORD CreateCutscene(struct Cutscene** cutscene, struct Animation* animations, size_t num_anims, int* offsets, int totaltime)
{
	*cutscene = NULL;

	*cutscene = malloc(sizeof(struct Cutscene));

	struct Cutscene* cs = *cutscene;
	if (cs == NULL) return E_OUTOFMEMORY;

	cs->Animations = animations;
	cs->_renderedframes = 0;
	cs->NumAnimations = num_anims;
	cs->TotalCutsceneTime = totaltime;

	if (offsets == NULL)
	{
		cs->Offsets = malloc(sizeof(int) * num_anims);
		if (cs->Offsets == NULL) return E_OUTOFMEMORY;
		memset(cs->Offsets, 0, sizeof(int) * num_anims);
	}

	return S_OK;
}

void DrawCutscene(struct Cutscene* cutscene)
{
	if (cutscene->TotalCutsceneTime <= cutscene->_renderedframes)
	{
		for (unsigned i = 0; i < cutscene->NumAnimations; i++)
		{
			COORD p1 = cutscene->Animations[i].initial_pos;
			COORD p2 = cutscene->Animations[i].to_pos;

			short pos_x = p1.X + (p2.X - p1.X) * ((float)cutscene->_renderedframes / cutscene->Animations[i].frames);
			short pos_y = p1.Y + (p2.Y - p1.Y) * ((float)cutscene->_renderedframes / cutscene->Animations[i].frames);

			COORD pos = { pos_x,pos_y };

			if (cutscene->Offsets[i] == 0)
				RenderSprite(cutscene->Animations[i].sprite, pos);
			else cutscene->Offsets[i] += 1;
		}
		cutscene->_renderedframes += 1;
		Sleep(1000);
	}
}

void DestroyAnimation(struct Animation* anim)
{
	free(anim);
}

void DestroyCutscene(struct Cutscene* cs)
{
	free(cs->Offsets);
	free(cs);
}

DWORD CreateDialogue(struct Dialogue** dialogue,char* text, int showtime, int speed, DWORD color)
{
	*dialogue = NULL;

	*dialogue = malloc(sizeof(struct Dialogue));
	struct Dialogue* d = *dialogue;
	
	if (d == NULL) return E_OUTOFMEMORY;

	d->Color = color;
	d->ShowTime = showtime;
	d->Speed = speed;
	d->Text = text;
	d->_renderedframes = 0;

	return S_OK;
}
void DrawDialogue(struct Dialogue* dialogue)
{
	for (unsigned i = 1; i < 100; i++)
	{
		COORD c1 = { i,50 }, c2 = { i,53 }, c3 = { i,51 }, c4 = { i,52 };
		SetScreenPixel(0x0F, c3);
		SetScreenPixel(0x0F, c4);
		SetScreenCharacter(0x0F, c1, '=');
		SetScreenCharacter(0x0F, c2, '=');
		COORD tc = { 5,52 };
		WriteScreen(0x0F, tc, dialogue->Text);
	}
}
void DestroyDialogue(struct Dialogue* dialogue)
{
	free(dialogue);
}