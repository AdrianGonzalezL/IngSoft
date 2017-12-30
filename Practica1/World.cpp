#include "World.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Mushroom.h"

// Implementacion de la clase mundo.
World::World(
	unsigned int     RANDOM_ENEMY_TIME,
	unsigned int     RANDOM_MUSHROOM_TIME,
	unsigned int     MAX_BULLETS,
	unsigned int     MAX_MAP,
	unsigned int     MAX_ENEMIES,
	int              score,
	unsigned int     lives,
	int              mushroomScore,
	unsigned int     dropTimeToFall)
{
	m_RANDOM_ENEMY_TIME    = RANDOM_ENEMY_TIME;
	m_RANDOM_MUSHROOM_TIME = RANDOM_MUSHROOM_TIME;
	m_MAX_BULLETS          = MAX_BULLETS;
	m_MAX_MAP              = MAX_MAP;
	m_MAX_ENEMIES          = MAX_ENEMIES;	
	m_score                = score;	
	m_lives                = lives;	
	m_mushroomScore        = mushroomScore;	
	m_dropTimeToFall       = dropTimeToFall;
	m_enemyTime            = m_RANDOM_ENEMY_TIME;
	m_mushroomTime         = m_RANDOM_MUSHROOM_TIME;
	m_escKeyPressed        = false;
	m_showMushroom         = false;
	m_mushroomPos          = 0;
	m_bullets              = 0;
	m_enemies              = 0;

	Player* p = new Player();
	int playerPos = m_MAX_MAP / 2;
	for (size_t i = 0; i < m_MAX_MAP; i++)
	{
		m_map.push_back(nullptr);
	}
	m_map[playerPos] = p;
	m_playerPos = playerPos;
	Mushroom* m = new Mushroom(m_mushroomScore);
	m_mushroomP = m;
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
		// Ponemos al jugador en la nueva casilla
		m_map[m_playerPos + pos] = m_map[m_playerPos];
		m_map[m_playerPos] = nullptr;
		(dir == Object::dir::LEFT) ? m_playerPos-- : m_playerPos++;
		// Comprobamos si ha recogido el champiñon
		if (m_playerPos == m_mushroomPos)
		{
			m_mushroomTime = m_RANDOM_MUSHROOM_TIME;
			m_showMushroom = false;
			m_score += m_mushroomP->m_score;
		}
	}
}

void World::createBullet(Object::dir dir)
{
	int pos;
	(dir == Object::dir::LEFT) ? pos = -1 : pos = 1;

	if (((dir == Object::dir::LEFT && m_playerPos > 0) || (dir == Object::dir::RIGHT && m_playerPos < m_MAX_MAP - 1)) && (m_bullets < m_MAX_BULLETS))
	{
		// Comprobamos si hay un enemigo en la posicion a crear la bala
		if (m_map[m_playerPos + pos] != nullptr && m_map[m_playerPos + pos]->m_type == Object::type::ENEMY)
		{
			delete m_map[m_playerPos + pos];
			m_map[m_playerPos + pos] = nullptr;
			m_enemies -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			m_score++;
		}
		// Si no hay enemigo creamos la bala
		else 
		{
			Bullet* b = new Bullet(dir);
			m_map[m_playerPos + pos] = b;
			m_bullets++;
		}
	}
}

void World::moveBullets()
{
	for (size_t i = 0; i < m_playerPos; i++)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::BULLET) { moveBullet(i); }
	}
	for (size_t i = m_MAX_MAP - 1; i > m_playerPos; i--)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::BULLET) { moveBullet(i); }
	}
}

void World::moveBullet(unsigned int posBullet)
{
	int posToMove;
	(static_cast<Bullet*>(m_map[posBullet])->m_dir == Object::dir::LEFT) ? posToMove = -1 : posToMove = 1;

	// Comprobamos si la bala se sale del mapa
	if ((posBullet == 0 && posToMove == -1) || (posBullet == m_MAX_MAP - 1 && posToMove == 1))
	{
		delete m_map[posBullet];
		m_map[posBullet] = nullptr;
		m_bullets--;
	}
	else
	{
		// Comprobamos si hay un enemigo en la posicion a mover la bala
		if (m_map[posBullet + posToMove] != nullptr && m_map[posBullet + posToMove]->m_type == Object::type::ENEMY)
		{
			delete m_map[posBullet + posToMove];
			m_map[posBullet + posToMove] = nullptr;
			m_enemies--;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			delete m_map[posBullet];
			m_map[posBullet] = nullptr;
			m_bullets--;
			m_score++;
		}
		// Si no hay enemigo movemos la bala
		else
		{
			m_map[posBullet + posToMove] = m_map[posBullet];
			m_map[posBullet] = nullptr;
		}
	}
}

void World::createEnemy()
{
	Object::dir dir;
	(rand() % 2 == 0) ? dir = Object::dir::LEFT : dir = Object::dir::RIGHT;

	// Comprobamos que no haya un enemigo en los extremos del mapa, que no haya ya tres enemigos, y que el timer de enemigo haya llegado a cero
	if  (((dir == Object::dir::RIGHT && (m_map[0]             == nullptr || m_map[0]->m_type             != Object::type::ENEMY))  ||
		  (dir == Object::dir::LEFT  && (m_map[m_MAX_MAP - 1] == nullptr || m_map[m_MAX_MAP - 1]->m_type != Object::type::ENEMY))) &&
		  (m_enemies < m_MAX_ENEMIES)&& 
		  (m_enemyTime < 0))
	{
		// Comprobamos si hay una bala en la posicion 0 a crear el enemigo
		if (dir == Object::dir::RIGHT && m_map[0] != nullptr && m_map[0]->m_type == Object::type::BULLET)
		{
			delete m_map[0];
			m_map[0] = nullptr;
			m_bullets -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			m_score++;
		}
		// Comprobamos si hay una bala en la posicion MAX - 1 a crear el enemigo
		else if (dir == Object::dir::LEFT  && m_map[m_MAX_MAP - 1] != nullptr && m_map[m_MAX_MAP - 1]->m_type == Object::type::BULLET)
		{
			delete m_map[m_MAX_MAP - 1];
			m_map[m_MAX_MAP - 1] = nullptr;
			m_bullets -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			m_score++;
		}
		// Comprobamos que no esta el player en la posicion MAX_MAP - 1 a crear el enemigo
		else if (dir == Object::dir::LEFT  && m_map[m_MAX_MAP - 1] != nullptr && m_map[m_MAX_MAP - 1]->m_type == Object::type::PLAYER)
		{
			m_lives -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
		}
		// Comprobamos que no esta el player en la posicion 0 a crear el enemigo
		else if (dir == Object::dir::RIGHT && m_map[0] != nullptr && m_map[0]->m_type == Object::type::PLAYER)
		{
			m_lives -= 1;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
		}
		// Si no hay bala ni jugador creamos el enemigo
		else
		{
			Enemy* e = new Enemy(dir);
			(dir == Object::dir::RIGHT) ? m_map[0] = e : m_map[m_MAX_MAP - 1] = e;
			m_enemies++;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
		}
	}
	// Si aun no es momento de crear enemigo, se reduce el timer de creacion de enemigos
	else { m_enemyTime -= 50; }
}

void World::moveEnemies()
{
	for (size_t i = m_playerPos - 1; i < UINT_MAX; i--)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::ENEMY) { moveEnemy(i); }
	}
	for (size_t i = m_playerPos + 1; i < m_MAX_MAP; i++)
	{
		if (m_map[i] != nullptr && m_map[i]->m_type == Object::type::ENEMY) { moveEnemy(i); }
	}
}

void World::moveEnemy(unsigned int posEnemy)
{
	int posToMove;
	(static_cast<Enemy*>(m_map[posEnemy])->m_dir == Object::dir::LEFT) ? posToMove = -1 : posToMove = 1;

	// Comprobamos si el enemigo hiere al jugador
	if (m_map[posEnemy + posToMove] != nullptr && m_map[posEnemy + posToMove]->m_type == Object::type::PLAYER)
	{
		delete m_map[posEnemy];
		m_map[posEnemy] = nullptr;
		m_enemies--;
		m_lives--;
	}
	else
	{
		// Comprobamos si hay una bala en la posicion a mover el enemigo
		if (m_map[posEnemy + posToMove] != nullptr && m_map[posEnemy + posToMove]->m_type == Object::type::BULLET)
		{
			delete m_map[posEnemy + posToMove];
			m_map[posEnemy + posToMove] = nullptr;
			m_bullets--;
			m_enemyTime = m_RANDOM_ENEMY_TIME;
			delete m_map[posEnemy];
			m_map[posEnemy] = nullptr;
			m_enemies--;
			m_score++;
		}
		// Si no hay bala movemos el enemigo
		else
		{
			m_map[posEnemy + posToMove] = m_map[posEnemy];
			m_map[posEnemy] = nullptr;
		}
	}
}

void World::showMushroom()
{
	if (m_mushroomTime < 0 && !m_showMushroom)
	{
		m_showMushroom = true;
		m_mushroomPos = rand() % m_MAX_MAP;
	}
	else { m_mushroomTime -= 50; }
}

void World::createDrop()
{
	if (rand() % 10 == 0)
	{
		// Buscaremos una posicion en la que no haya ya una gota
		bool usedValue = true;
		unsigned int pos = 0;
		while (usedValue)
		{
			usedValue = false;
			pos = rand() % m_MAX_MAP;
			for (auto it = m_drops.begin(); it != m_drops.end(); it++)
			{
				if ((*it)->m_pos == pos && !usedValue) { usedValue = true; }
			}
		}
		Drop* d = new Drop(pos, m_dropTimeToFall);
		m_drops.push_back(d);
	}
}

void World::updateDrops()
{
	auto it = m_drops.begin();
	while (it != m_drops.end())
	{
		(*it)->update();
		if ((*it)->m_timer == 0)
		{ 
			delete *it;
			it = m_drops.erase(it); 
		}
		else { it++; }
	}
}

void World::printWorld()
{
	for (size_t i = 0; i < m_MAX_MAP; i++)
	{
		// Los enemigos se mostraran por encima del champiñon y las gotas
		if      (m_map[i] != nullptr)                   { m_map[i]->printObject(); }
		else if (m_showMushroom && i == m_mushroomPos)  { m_mushroomP->printObject(); }
		else
		{
			bool gota = false;
			for (auto it = m_drops.begin(); it != m_drops.end(); it++)
			{
				if ((*it)->m_pos == i) 
				{
					(*it)->printObject();
					gota = true;
				}

			}
			if (!gota){ printf("_"); }
		}
	}
}

void World::deleteWorld()
{
	for (size_t i = 0; i < m_MAX_MAP; i++)
	{
		if (m_map[i] != nullptr) { delete m_map[i]; }
	}
	for (size_t i = 0; i < m_drops.size(); i++)
	{
		delete m_drops[i];
	}
	delete m_mushroomP;
}