#pragma once
#include "Object.h"

struct Mushroom : public Object
{
	int m_score = 5;

	Mushroom();
	void printObject();
};