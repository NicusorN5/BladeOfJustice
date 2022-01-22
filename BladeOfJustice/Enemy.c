#include "Enemy.h"

void CreateEnemy(Enemy* enemy, int BaseHealth, int BaseDamage, int PelletsPerAttack, EnemyAttackFptr* attack_pattern,Sprite * spr)
{
	enemy->AttackPattern = attack_pattern;
	enemy->Damage = BaseDamage;
	enemy->Health = BaseHealth;
	enemy->Pellets = PelletsPerAttack;
	enemy->Sprite = spr;
}
