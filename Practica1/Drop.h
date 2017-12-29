#pragma once
#include "Object.h"

struct Drop : public Object
{
	enum state {S1,S2,S3};
	state m_state;
	int m_timer = 1000;
	int m_pos;

	Drop(int pos);
	void update();
	void printObject();
};