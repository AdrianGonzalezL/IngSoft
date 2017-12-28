#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>  
#pragma warning(disable:4820)

Bullet::Bullet()
{
	m_type = BULLET;
	(rand() % 2 == 0) ? m_dir = RIGHT : m_dir = LEFT;
}

void Bullet::printObject()
{
	(m_dir == LEFT) ? printf("<") : printf(">");
}
