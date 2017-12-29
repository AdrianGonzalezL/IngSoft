#include "World.h"
#include "Player.h"
#include "Bullet.h"
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
			m_map[m_playerPos + pos] = nullptr;
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

void World::createBullet(Object::dir dir)
{
	int pos;
	(dir == Object::dir::LEFT) ? pos = -1 : pos = 1;

	if ((dir == Object::dir::LEFT && m_playerPos > 0) || ((dir == Object::dir::RIGHT && m_playerPos < m_MAX_MAP - 1)))
	{
		// Comprobamos si hay un enemigo en la posicion a crear la bala
		if (m_map[m_playerPos + pos] != nullptr && m_map[m_playerPos + pos]->m_type == Object::type::ENEMY)
		{
			delete m_map[m_playerPos + pos];
			m_map[m_playerPos + pos] = nullptr;
			m_enemies -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
		}
		// Si no hay enemigo creamos la bala
		else 
		{
			Bullet* b = new Bullet(dir);
			m_map[m_playerPos + pos] = b;
		}
	}
}

void World::moveBullets()
{
	for (int i = 0; i < m_playerPos; i++)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::BULLET)
		{
			moveBullet(i);
		}
	}
	for (int i = m_MAX_MAP - 1; i > m_playerPos; i--)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::BULLET)
		{
			moveBullet(i);
		}
	}
}

void World::moveBullet(int posBullet)
{
	int posToMove;
	(static_cast<Bullet*>(m_map[posBullet])->m_dir == Object::dir::LEFT) ? posToMove = -1 : posToMove = 1;

	// Comprobamos si la bala se sale del mapa
	if ((posBullet == 0 && posToMove == -1) || (posBullet == m_MAX_MAP - 1 && posToMove == 1))
	{
		delete m_map[posBullet];
		m_map[posBullet] = nullptr;
	}
	else
	{
		// Comprobamos si hay un enemigo en la posicion a mover la bala
		if (m_map[posBullet + posToMove] != nullptr && m_map[posBullet + posToMove]->m_type == Object::type::ENEMY)
		{
			delete m_map[posBullet + posToMove];
			m_map[posBullet + posToMove] = nullptr;
			m_enemies -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			delete m_map[posBullet];
			m_map[posBullet] = nullptr;
		}
		// Si no hay enemigo movemos la bala
		else
		{
			m_map[posBullet + posToMove] = m_map[posBullet];
			m_map[posBullet] = nullptr;
		}
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

void World::deleteWorld()
{
	for (int i = 0; i < m_MAX_MAP; i++)
	{
		if (m_map[i] != nullptr)
		{
			delete m_map[i];
		}
	}
}
