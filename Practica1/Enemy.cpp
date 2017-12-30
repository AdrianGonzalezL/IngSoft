#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>  

// Implementacion de la clase enemigo.
Enemy::Enemy(Object::dir dir)
{
	m_type = ENEMY;
	m_dir  = dir;
}

void Enemy::printObject()
{
	printf("@");
}