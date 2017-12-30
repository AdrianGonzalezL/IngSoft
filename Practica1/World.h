#pragma once
#include "Object.h"
#include "Mushroom.h"
#include "Drop.h"
#include <vector>

using namespace std;

// Clase que ademas de ser el gestor meteorologico, gestiona todos los elementos que se muestran por la pantalla.
// Esta clase contiene el mapa y las diferentes variables que controlan el estado de la partida.
struct World
{
	unsigned int     m_RANDOM_ENEMY_TIME;
	unsigned int     m_RANDOM_MUSHROOM_TIME;
	unsigned int     m_MAX_BULLETS;
	unsigned int     m_MAX_MAP;
	unsigned int     m_MAX_ENEMIES;
	bool             m_escKeyPressed;
	int              m_score;
	int              m_enemyTime;
	int              m_mushroomTime;
	unsigned int     m_bullets;
	unsigned int     m_enemies;
	unsigned int     m_lives;
	unsigned int     m_playerPos;
	vector<Object*>  m_map;
	unsigned int     m_mushroomPos;
	int              m_mushroomScore;
	Mushroom*        m_mushroomP;
	bool             m_showMushroom;
	vector<Drop*>    m_drops;
	unsigned int     m_dropTimeToFall;

	World(
		unsigned int     RANDOM_ENEMY_TIME,
		unsigned int     RANDOM_MUSHROOM_TIME,
		unsigned int     MAX_BULLETS,
		unsigned int     MAX_MAP,
		unsigned int     MAX_ENEMIES,
	    int              score,
		unsigned int     lives,
	    int              mushroomScore,
	    unsigned int     dropTimeToFall);

	void movePlayer(Object::dir dir);
	void createBullet(Object::dir dir);
	void moveBullets();
	void moveBullet(unsigned int posBullet);
	void createEnemy();
	void moveEnemies();
	void moveEnemy(unsigned int posEnemy);
	void showMushroom();
	void createDrop();
	void updateDrops();
	void printWorld();
	void deleteWorld();
};