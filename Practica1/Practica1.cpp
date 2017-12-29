// Adrian Gonzalez Lopez
// Practica de Ingenieria de Software

// Dia 1:
// Usar printf para imprimir por pantalla el juego
// Kbhit() te devuelve si se ha pulsado una tecla, usar para los controles
// \r retorno de carro para pintar la misma linea
// Con escape se sale del bucle.
// Si se pulsa la A o la D se mueve la X para la izquierda y la derecha
// Si se pulsa la J o la L se dispara una bala para la izquierda o la derecha
// Cada cierto tiempo aparece un enemigo, en la izquierda o la dcha, que va hacia tu posicion, y si choca contigo te quita vida. Si le da una bala, muere el.
// Que aparezca un champiñon que te de puntos
// Mostrar el numero de vidas que te quedan, y los puntos que tienes, en la misma linea que el mapa.

// Dia 2 (esta version se entrega):
// Poder disparar varias balas. Usar un struct bala {int x; dir} y luego std::list <bala>
// Que aparezcan varios enemigos

// Dia 3 (esta version se entrega):
// Organizar el codigo en clases, en distintos modulos, sin usar herencia.
// Clases enemigo, bala, jugador
// Clase gestor metereologico: cuando se pinta, se pregunta a esta clase que hay que pintar, ya que esta clase es la que gestiona internamente donde estan y el estado de las gotas
// Para imprimir las gotas, se pueden usar varios iconos:  gota "'", tocando el suelo ",", desapareciendo "."

// Dia 4 (esta version se entrega):
// Grabar un video jugando al juego

#pragma once
#pragma warning(disable:4710)
#pragma warning(disable:4668)
#pragma warning(disable:5039)
#pragma warning(disable:4820)
#pragma warning(disable:4365)
#pragma warning(disable:4623)
#pragma warning(disable:4571)
#pragma warning(disable:4820)


#include "Object.h"
#include "World.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <list>

using namespace std;

#define ESC_KEY 27
#define A_KEY   'a'
#define D_KEY   'd'
#define J_KEY   'j'
#define L_KEY   'l'

// Funcion que determina que enemigos han sido alcanzados en un frame del juego
//void enemyReached(list<Object>& bullets, list<Object>& enemies, int& score, int& enemyTime, int RANDOM_ENEMY_TIME) 
//{
//	for (auto itb = bullets.begin(); itb != bullets.end(); itb++) 
//	{
//		for (auto ite = enemies.begin(); ite != enemies.end(); ite++) 
//		{
//			if (itb->m_pos == ite->m_pos) 
//			{
//				itb->m_pos    =  -10;
//				ite->m_pos    =  -10;
//				score         += 1;
//				enemyTime     =  RANDOM_ENEMY_TIME;
//			}
//		}
//	}
//}

// Funcion que determina si el juegador ha sido alcanzado
//void playerReached(const int& playerPos, list<Object>& enemies, int& lives, int& enemyTime, int RANDOM_ENEMY_TIME) 
//{
//	for (auto ite = enemies.begin(); ite != enemies.end(); ite++) 
//	{
//		if (ite->m_pos == playerPos) 
//		{
//			ite->m_pos    =  -10;
//			lives         -= 1;
//			enemyTime     =  RANDOM_ENEMY_TIME;
//		}
//	}
//}

// Funcion que determina si en una posicion del mapa hay una bala, y devuelve la direccion de la bala.
//dir dirBullet(int pos, list<Object>& bullets) 
//{
//	dir bulletDir = dir::NONE;
//	for (auto it = bullets.begin(); it != bullets.end(); it++) 
//	{
//		if (it->m_pos == pos) { bulletDir = it->m_dir; }
//	}
//	return bulletDir;
//}

// Funcion que determina si en una posicion del mapa hay un enemigo
//bool isEnemy(int pos, list<Object>& enemies) 
//{
//	bool isEne = false;
//	for (auto ite = enemies.begin(); ite != enemies.end(); ite++) 
//	{
//		if (ite->m_pos == pos) { isEne = true; }
//	}
//	return isEne;
//}

// Funcion que hace avanzar una posicion cada elemento de una lista de objetos, y si se encuentran fuera del mapa, los elimina de la lista
//void moveObjects(list<Object>& list, int MAX_MAP_POS) 
//{
//	auto it = list.begin();
//	while (it != list.end()) 
//	{
//		if (it->m_dir == dir::LEFT)                       { it->m_pos--; }
//		else                                              { it->m_pos++; }
//		if ((it->m_pos < 1) || (it->m_pos > MAX_MAP_POS)) { it = list.erase(it); }
//		else                                              { it++; }
//	}
//}

// Funcion que comprueba si es el momento de crear un enemigo nuevo, y que no haya ya un enemigo en la primera o ultima posicion del mapa
//void createEnemies(list<Object>& enemies, int& enemyTime, int MAX_ENEMIES, int RANDOM_ENEMY_TIME, int MAX_MAP_POS) 
//{
//	if ((enemyTime <= 0) && (enemies.size() < static_cast<unsigned int>(MAX_ENEMIES))) 
//	{
//		if ((rand() % 2) == 0) 
//		{
//			bool firstPosEnemy = false;
//			for (auto ite = enemies.begin(); ite != enemies.end(); ite++) 
//			{
//				if (ite->m_pos == 1) { firstPosEnemy = true; }
//			}
//			if (!firstPosEnemy) 
//			{
//				enemies.push_back(Object(1, dir::RIGHT));
//				enemyTime = RANDOM_ENEMY_TIME;
//			}
//		}
//		else 
//		{
//			bool lastPosEnemy = false;
//			for (auto ite = enemies.begin(); ite != enemies.end(); ite++) 
//			{
//				if (ite->m_pos == MAX_MAP_POS) { lastPosEnemy = true; }
//			}
//			if (!lastPosEnemy) 
//			{
//				enemies.push_back(Object(MAX_MAP_POS, dir::LEFT));
//				enemyTime = RANDOM_ENEMY_TIME;
//			}
//		}
//	}
//	else { enemyTime -= 50; }
//}

// Funcion que comprueba si es el momento de que aparezca un champiñon
//void createMushroom(int& mushroomPos, int& mushroomTime, int MAX_MAP_POS) 
//{
//	if ((mushroomPos < 0) && (mushroomTime < 0)) { mushroomPos = (rand() % MAX_MAP_POS + 1); }
//	else { mushroomTime -= 50; }
//}

// Funcion que compueba si el jugador ha recogido el champiñon
//void mushroomReached(int& playerPos, int& mushroomPos, int& mushroomTime, int& score, int RANDOM_MUSHROOM_TIME) 
//{
//	if (playerPos == mushroomPos) 
//	{
//		mushroomPos = -1;
//		mushroomTime = RANDOM_MUSHROOM_TIME;
//		score += 5;
//	}
//}

int main()
{
	// Si es negativa la posicion de un objeto: no existe.	
	int CONSOLE_WIDTH  = 1000;
	int CONSOLE_HEIGHT = 400;

	// Modificamos la dimension de la consola
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, TRUE);

	//Pintamos las instrucciones
	printf("\n\n");
	printf("Movimiento: A y D. Disparo: J y L. Salir: ESC.\nSolo puedes disparar tres balas de forma consecutiva.\n\n");
	printf("Pulse intro para iniciar la partida.\n");
	getchar();
	printf("\n\n");

	// Creamos una instancia de World
	World world;

	// Bucle del juego
	while ((!world.m_escKeyPressed) && (world.m_lives > 0)) 
	{
		// Comprobamos si se ha pulsado una tecla, y se comprueba cual (movimiento / disparo jugador)
		if (_kbhit()) 
		{
			switch (_getch()) 
			{
				case ESC_KEY: world.m_escKeyPressed = true;           break;
				case A_KEY:   world.movePlayer(Object::dir::LEFT);    break;
				case D_KEY:   world.movePlayer(Object::dir::RIGHT);   break;
				case L_KEY:   world.createBullet(Object::dir::RIGHT); break;
				case J_KEY:   world.createBullet(Object::dir::LEFT);  break;
			}
		}

		// Movemos las balas
		world.moveBullets();

		// Comprobamos que el enemigo mata al jugador
		//playerReached(playerPos, enemies, lives, enemyTime, RANDOM_ENEMY_TIME);

		// Si esta el enemigo, avanza, si esta fuera del mapa, se elimina
		//moveObjects(enemies, MAX_MAP_POS);

		// Comprobamos si aparece el enemigo y que no haya otro enemigo en la posicion en la que va a aparecer
		//createEnemies(enemies, enemyTime, MAX_ENEMIES, RANDOM_ENEMY_TIME, MAX_MAP_POS);

		// Comprobamos que la bala mata al enemigo
		//enemyReached(bullets, enemies, score, enemyTime, RANDOM_ENEMY_TIME);

		// Comprobamos que el enemigo mata al jugador
		//playerReached(playerPos, enemies, lives, enemyTime, RANDOM_ENEMY_TIME);

		// Comprobamos si sale el champiñon
		//createMushroom(mushroomPos, mushroomTime, MAX_MAP_POS);

		// Comprobamos que el jugador recoge el champiñon
		//mushroomReached(playerPos, mushroomPos, mushroomTime, score, RANDOM_MUSHROOM_TIME);

		// Pintamos el mapa
		printf("\r");		
		world.printWorld();

		// Pintamos las vidas y la puntuacion
		printf("     vidas: %i, puntuacion: %i.", world.m_lives, world.m_score);
		Sleep(50);
	}

	// Fin de la partida.
	printf("\n\nPuntuacion final : %i.\n", world.m_score);
	printf("Pulse intro para salir.");
	world.deleteWorld();
	getchar();
    return 0;
}