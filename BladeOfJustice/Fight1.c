#include "Fight1.h"

int selection;
struct Dialogue *BattleBar;

int beingAttacked = 0;
int attacking = 0;
COORD PlayerPos;
Enemy Skeleton;

Pellete Pellets[1000];

void Skeleton_Attack_Pattern(Pellete* p)
{
	for(size_t i = 0; i < Skeleton.Pellets; i++)
	{
		srand(time(NULL)); 

		Pellete projectile;
		projectile.chr = '#';
		projectile.Damage = Skeleton.Damage;
		projectile.Pos.X = rand() % 100;
		projectile.Pos.Y = rand() % 50;

		//vx,vy formeaza un vector 2D de directie, proiectilul se indreapta spre player
		float vx = projectile.Pos.X - PlayerPos.X;
		float vy = projectile.Pos.Y - PlayerPos.Y;

		float vl = hypotf(vx, vy); //formula de normalizare a unui vector : \sqrt{ x \cdot x + y \cdot y}
		vx /= vl;
		vy /= vl;

		projectile.Direction.x = vx;
		projectile.Direction.y = vy;

		projectile.Enabled = TRUE;
		projectile.Speed = 2;
	}
}

DWORD Fight1_Initialize()
{
	InitializePlayerDefaultValues(&MainPlayer);

	DWORD r = CreateDialogue(&BattleBar, "", 5, 5, 0x0F); if(r != S_OK) return r;

	beingAttacked = 0;

	PlayerPos.X = 50;
	PlayerPos.Y = 20;

	Sprite* skeleton;
	COORD skeleton_sprite_size = {7,21};
	DWORD f = CreateSpriteFromFile(&skeleton, "Sprites\\Skeleton.bojimg", skeleton_sprite_size); if(f < 0) return f;

	CreateEnemy(&Skeleton, 100, 5, 5, NULL, skeleton);

	for(size_t i = 0; i < 1000; i++)
	{
		Pellets[i].Enabled = FALSE;
	}

	return S_OK;
}

int attack_timer = 0;
int crit_hit = 5;

void Fight1_Draw(float dt)
{
	if(attacking)
	{
		attack_timer += 1;

		static char text[32];
		memset(text, ' ', 32);
		text[0] = ']';
		text[attack_timer] = '*';
		text[crit_hit] = '<';
		text[31] = 0;

		BattleBar->Text = text;
		DrawDialogue(BattleBar);
		COORD enemy_pos = { 50,0 };
		RenderSprite(Skeleton.Sprite, enemy_pos);

		attack_timer--;

		if(attack_timer == 0) attacking = FALSE;
	}
	else if(beingAttacked)
	{
		SetScreenCharacter(04, PlayerPos, '@');
		for(size_t i = 0; i < 1000; i++)
		{
			RenderPellete(Pellets + i);
			UpdatePellete(Pellets + i, PlayerPos);
		}
	}
	else
	{
		static char battletext[60];
		memset(battletext, 0, 60);
		switch(selection)
		{
			case 0:
			{
				BattleBar->Text = ">Attack< Item Run";
				break;
			}
			case 1:
			{
				BattleBar->Text = "Attack >Item< Run";
				break;
			}
			case 2:
			{
				BattleBar->Text = "Attack Item >Run<";
				break;
			}
			default: 
			{
				selection = Clamp(0, selection, 2);
				Fight1_Draw(dt); //nu mai rescriu switch-case-ul, folosesc un apel recursiv in schimb
				break;
			}
		}
		DrawDialogue(BattleBar);
		char enemy_stats[60],player_stats[60];
		memset(enemy_stats, 0, 60);
		memset(player_stats, 0, 60);

		sprintf(enemy_stats, "%s Health: %d DMG %d", "Skeleton", Skeleton.Health, Skeleton.Damage);
		sprintf(player_stats, "Your health: %i", MainPlayer.Health);

		COORD tc = { 5,53 },plr_stats_txtpos = {5,54};
		WriteScreen(0x04, tc, enemy_stats);
		WriteScreen(0x0A, plr_stats_txtpos,player_stats);
		
		COORD enemy_pos = { 50,0 };
		RenderSprite(Skeleton.Sprite,enemy_pos);
	}
}

void Fight1_Input(DWORD key)
{
	if(attacking)
	{
		switch(key)
		{
			case VK_RETURN:
			case VK_SPACE:
			{
				attacking = FALSE;
				if(attack_timer == crit_hit)
				{
					Skeleton.Health -= 50 * MainPlayer.WeaponID;
				}
				else Skeleton.Health -= 10 * MainPlayer.WeaponID;
				break;
			}
			default: break;
		}
	}
	else if(beingAttacked)
	{
		switch(key)
		{
			case VK_LEFT:
				PlayerPos.X -= 1;
				break;
			case VK_RIGHT:
				PlayerPos.X += 1;
				break;
			case VK_UP:
				PlayerPos.Y -= 1;
				break;
			case VK_DOWN:
				PlayerPos.Y += 1;
				break;
			default: break;
		}
		PlayerPos.X = Clamp(0, PlayerPos.X, 800);
		PlayerPos.Y = Clamp(0, PlayerPos.Y, 600);
	}
	else
	{
		switch(key)
		{
			case VK_LEFT:
				selection--;
				break;
			case VK_RIGHT:
				selection++;
				break;
			case VK_SPACE:
			case VK_RETURN:
			{
				switch(selection)
				{
					case 0:
					{
						attacking = TRUE;
						break;
					}
					case 1:
					{
						//TODO: insert item interface;
						break;
					}
					case 2:
					{
						srand(time(NULL));
						int rnd = rand() % 15;
						if(rnd == 0)
						{
							GameLevel += 1; //sanse ~1/15 sa poti fugi de schelete
						}
						else beingAttacked = TRUE;
						break;
					}
					default: break;
				}
				break;
			}
			case VK_ESCAPE:
				GameSection = gamepart_MainMenu;
				break;
			default: break;
		}
	}
}
