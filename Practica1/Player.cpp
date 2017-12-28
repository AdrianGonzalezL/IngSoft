#include "Player.h"
#include <stdio.h> 
#pragma warning(disable:4820)

Player::Player()
{
	m_type = PLAYER;
}

void Player::printObject()
{
	printf("X");
}
