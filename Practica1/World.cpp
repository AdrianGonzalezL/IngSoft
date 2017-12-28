#include "World.h"
#include "Player.h"
#pragma warning(disable:4820)

World::World()
{
	Player* p = new Player();
	int playerPos = m_MAX_MAP / 2;
	for (int i = 0; i < m_MAX_MAP; i++)	{ m_map.push_back(nullptr);	}
	m_map[playerPos] = p;
	m_playerPos = playerPos;
}

void World::movePlayer(Object::dir dir)
{
	int pos;
	(dir == Object::dir::LEFT) ? pos = -1 : pos = 1;

	if ((dir == Object::dir::LEFT && m_playerPos > 0) || ((dir == Object::dir::RIGHT && m_playerPos < m_MAX_MAP - 1)))
	{
		// Si te mueves a una casilla con enemigo
		if (m_map[m_playerPos + pos] != nullptr && m_map[m_playerPos + pos]->m_type == Object::type::ENEMY)
		{
			m_lives -= 1;
			delete m_map[m_playerPos + pos];
			m_enemies -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
		}
		// A una casilla con champiñon
		// A una casilla con una gota
		// Ponemos al jugador en la nueva casilla
		m_map[m_playerPos + pos] = m_map[m_playerPos];
		m_map[m_playerPos] = nullptr;
		(dir == Object::dir::LEFT) ? m_playerPos-- : m_playerPos++;
	}
}

void World::printWorld()
{
	for (int i = 0; i < m_MAX_MAP; i++)
	{
		if (m_map[i] != nullptr) { m_map[i]->printObject(); }
		else { printf("_"); }
	}
}
