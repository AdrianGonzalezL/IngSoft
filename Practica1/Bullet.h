#pragma once
#include "Object.h"

struct Bullet : public Object
{
	dir m_dir;

	Bullet(dir dir);
	void printObject();
};