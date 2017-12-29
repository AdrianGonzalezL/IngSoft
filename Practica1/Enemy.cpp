#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>  
#pragma warning(disable:4820)

Enemy::Enemy(Object::dir dir)
{
	m_type = ENEMY;
	m_dir  = dir;
}

void Enemy::printObject()
{
	printf("@");
}
