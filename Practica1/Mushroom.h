#pragma once
#include "Object.h"

// Clase para crear champi�ones.
struct Mushroom : public Object
{
	int m_score;

	Mushroom(int score);
	void printObject();
};