#pragma once
#include "Object.h"
#include "Mushroom.h"
#include "Drop.h"
#include <vector>

using namespace std;

struct World
{
	int              m_RANDOM_ENEMY_TIME    = (rand() % 4 + 1) * 100;
	int              m_RANDOM_MUSHROOM_TIME = (rand() % 7 + 1) * 1000;
	int              m_MAX_BULLETS          = 3;
	static const int m_MAX_MAP              = 40;
	int              m_MAX_ENEMIES          = 3;
	bool             m_escKeyPressed        = false;
	int              m_score                = 0;
	int              m_enemyTime            = m_RANDOM_ENEMY_TIME;
	int              m_mushroomTime         = m_RANDOM_MUSHROOM_TIME;
	int              m_bullets              = 0;
	int              m_enemies              = 0;
	int	             m_lives                = 3;
	int              m_playerPos            = 0;
	vector<Object*>  m_map;
	int              m_posMushroom          = 0;
	Mushroom*        m_mushroomP            = nullptr;
	bool             m_showMushroom         = false;
	vector<Drop*>    m_drops;

	World();
	void movePlayer(Object::dir dir);
	void createBullet(Object::dir dir);
	void moveBullets();
	void moveBullet(int posBullet);
	void createEnemy();
	void moveEnemies();
	void moveEnemy(int posEnemy);
	void showMushroom();
	void createDrop();
	void updateDrops();
	void printWorld();
	void deleteWorld();
};