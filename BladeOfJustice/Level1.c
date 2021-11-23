#include "Level1.h"

struct Animation Animations[5];

struct Cutscene* IntroCutscene;

struct Sprite* Temple, *God, *Book1, *Book2, *Book3, *Guardian,*Sword;

struct Dialogue* d1;

DWORD Cutscene1_Load()
{
	//No, I'm not going to use macros

	//But I agree that this is too much boilerplate code.

	COORD d32x32 = { 32,32 }, zeropos = { 0,0 };
	DWORD r ;
	r = CreateSpriteFromFile(&Temple, "Sprites//Temple.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&God, "Sprites//God.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&Book1, "Sprites//Book1.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&Book2, "Sprites//Book2.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&Book3, "Sprites//Book3.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&Guardian, "Sprites//Guardian.bojimg", d32x32); if (r != S_OK) return r;
	r = CreateSpriteFromFile(&Sword, "Sprites//Sword.bojimg", d32x32); if (r != S_OK) return r;

	r = CreateAnimation(&Animations[0], God, zeropos, zeropos, 5); if (r != S_OK) return r;
	r = CreateAnimation(&Animations[1], Book1, zeropos, zeropos, 5 ); if (r != S_OK) return r;
	r = CreateAnimation(&Animations[2], Book2, zeropos, zeropos, 5); if (r != S_OK) return r;
	r = CreateAnimation(&Animations[3], Book3, zeropos, zeropos, 5); if (r != S_OK) return r;
	r = CreateAnimation(&Animations[4], Guardian, zeropos, zeropos, 5); if (r != S_OK) return r;
	r = CreateAnimation(&Animations[5], Temple, zeropos, zeropos, 5); if (r != S_OK) return r;

	r = CreateCutscene(&IntroCutscene, Animations, 5, NULL, 100); if (r != S_OK) return r;

	r = CreateDialogue(&d1, "Once upon a time...", 5, 5, 0x0F); if (r != S_OK) return r;

	return S_OK;
}

int CutSceneDrawn = 0;

void Cutscene1_Draw(float dt)
{
	if (CutSceneDrawn == 1) return;
	//DrawCutscene(IntroCutscene);

	//I'm using the most stupid method to draw cutscenes : I'm going everything like I'm unrolling loops myself smh
	//I should feel ashamed

	//PlaySoundA("Music//Ost1_TheLegend.wav", NULL, SND_ASYNC | SND_FILENAME); //TODO: Enable/disable music in settings

	ClearColor = 0x10;
	ClearScreenWithColor(ClearColor);
	COORD zeropos = { 0,0 };
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	COORD center = { 100,0 }, drop_book1 = { 125,20 }, drop_book2 = { 75,20 };
	d1->Text = "The Gods sent us few gifts...";
	ClearScreenWithColor(ClearColor);
	RenderSprite(God, center);
	RenderSprite(Book1, drop_book1);
	RenderSprite(Book2, drop_book2);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	d1->Text = "The supreme book of magic...";
	ClearScreenWithColor(ClearColor);
	RenderSprite(Book1, zeropos);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	COORD p[] = { {32,0}, {0,16},{32,16} };
	d1->Text = "The supreme book of nature...";
	ClearScreenWithColor(ClearColor);
	RenderSprite(Book1, zeropos);
	RenderSprite(Book2, p[0]);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	d1->Text = "The supreme book of knowledge...";
	ClearScreenWithColor(0x00);
	RenderSprite(Book1, zeropos);
	RenderSprite(Book2, p[0]);
	RenderSprite(Book3, p[1]);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	d1->Text = "And the most important of them all. The Blade of justice.";
	ClearScreenWithColor(0x40);
	PrintScreen();
	RenderSprite(Sword, center);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);

	d1->Text = "The legend says they are hidden in a temple.";
	ClearScreenWithColor(0x70);
	PrintScreen();
	RenderSprite(Temple, center);
	DrawDialogue(d1);
	PrintScreen();
	Sleep(5000);
	ClearColor = 0x00;

	PlaySound(NULL, 0, 0);
	CutSceneDrawn = 1;
	GameLevel = 1;
}

void Cutscene1_Destroy()
{
	DestroyCutscene(IntroCutscene);
}
