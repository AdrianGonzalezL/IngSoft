#pragma once
#include "Object.h"

struct Enemy : public Object
{
	dir m_dir;

	Enemy();
	void printObject();
};