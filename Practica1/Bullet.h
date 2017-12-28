#pragma once
#include "Object.h"

struct Bullet : public Object
{
	dir m_dir;

	Bullet();
	void printObject();
};