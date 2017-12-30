#pragma once
#include "Object.h"

// Clase para crear gotas de lluvia.
struct Drop : public Object
{
	enum state {S1,S2,S3};
	state m_state;
	unsigned int m_timer;
	unsigned int m_pos;

	Drop(unsigned int pos, unsigned int timer);
	void update();
	void printObject();
};