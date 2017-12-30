#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>  

// Implementacion de la clase bala.
Bullet::Bullet(dir dir)
{
	m_type = BULLET;
	m_dir  = dir;
}

void Bullet::printObject()
{
	(m_dir == LEFT) ? printf("<") : printf(">");
}