#pragma once
#include "Sprite.h"

/*
* 
* NONE OF THIS IS WORKING !!!!!!!!!!11 AAAAAAAAAAAAAAAAAAAAAAAH
* 
*/

struct Animation
{
	Sprite* sprite;
	COORD initial_pos,to_pos;
	int frames;
};

struct Cutscene
{
	struct Animation* Animations;
	size_t NumAnimations;
	int _renderedframes;
	int* Offsets;
	int TotalCutsceneTime;
};

DWORD CreateAnimation(struct Animation** animation,Sprite* affected_sprite, COORD initial_pos, COORD final_pos,int frames);
void DestroyAnimation(struct Animation* anim);

DWORD CreateCutscene(struct Cutscene** cutscene,struct Animation* animations,size_t num_anims, int* offsets, int totaltime);
void DrawCutscene(struct Cutscene* cutscene);
void DestroyCutscene(struct Cutscene* cs);

struct Dialogue
{
	char* Text;
	int ShowTime;
	int _renderedframes;
	int Speed;
	DWORD Color;
};

DWORD CreateDialogue(struct Dialogue** dialogue,char* text, int showtime, int speed, DWORD color);
void DrawDialogue(struct Dialogue * dialogue);
void DestroyDialogue(struct Dialogue* dialogue);