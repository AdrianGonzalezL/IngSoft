#include "Drop.h"
#include <stdio.h>

Drop::Drop(int pos)
{
	m_type  = DROP;
	m_state = S1;
	m_pos   = pos;
}

void Drop::update()
{
	m_timer -= 50;
	if      (m_timer > 600) { m_state = S3; }
	else if (m_timer > 300) { m_state = S2; }
	else                    { m_state = S1; }
}

void Drop::printObject()
{
	switch (m_state)
	{
		case S3: printf("'"); break;
		case S2: printf(","); break;
		case S1: printf("."); break;
	}
}
