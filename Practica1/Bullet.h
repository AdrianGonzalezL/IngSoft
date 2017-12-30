#pragma once
#include "Object.h"

// Clase para crear balas.
struct Bullet : public Object
{
	dir m_dir;

	Bullet(dir dir);
	void printObject();
};