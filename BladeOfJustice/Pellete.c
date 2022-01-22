#include "Pellete.h"

void RenderPellete(Pellete* p)
{
	if(p->Enabled)
	{
		SetScreenCharacter(0x04, p->Pos, p->chr);
	}
}

void UpdatePellete(Pellete* p,COORD playerPos)
{
	if(p->Enabled)
	{
		if(p->Pos.X == playerPos.X && p->Pos.Y == playerPos.Y)
		{
			MainPlayer.Health -= p->Damage;
			p->Enabled = FALSE;
		}

		p->Pos.X += p->Direction.x * p->Speed;
		p->Pos.Y += p->Direction.y * p->Speed;
	}
}
