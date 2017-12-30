#pragma once
#include "Object.h"

// Clase para crear enemigos.
struct Enemy : public Object
{
	dir m_dir;

	Enemy(Object::dir dir);
	void printObject();
};