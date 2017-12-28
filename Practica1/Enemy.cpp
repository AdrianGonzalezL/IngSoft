#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>  
#pragma warning(disable:4820)

Enemy::Enemy()
{
	m_type = ENEMY;
	(rand() % 2 == 0) ? m_dir = RIGHT : m_dir = LEFT;
}

void Enemy::printObject()
{
	printf("@");
}
