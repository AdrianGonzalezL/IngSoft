#pragma once
#include "Object.h"

struct Enemy : public Object
{
	dir m_dir;

	Enemy(Object::dir dir);
	void printObject();
};