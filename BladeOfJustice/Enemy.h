#pragma once
#include "Sprite.h"
#include "Pellete.h"

typedef void (*EnemyAttackFptr)(Pellete* pellete_array);

typedef struct _objEnemy
{
	int Health;
	int Damage;
	int Pellets;
	Sprite* Sprite;
	EnemyAttackFptr AttackPattern;
} Enemy;

void CreateEnemy(Enemy* enemy, int BaseHealth, int BaseDamage, int PelletsPerAttack, EnemyAttackFptr* attack_pattern,Sprite * sprite);