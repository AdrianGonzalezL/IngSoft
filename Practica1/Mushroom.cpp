#include "Mushroom.h"
#include <stdio.h>

// Implementacion de la clase champi�on.
Mushroom::Mushroom(int score)
{
	m_type  = MUSHROOM;
	m_score = score;
}

void Mushroom::printObject()
{
	printf("T");
}