// Adrian Gonzalez Lopez
// Practica de Ingenieria de Software

// Dia 1:
// Usar printf para imprimir
// Kbhit() te devuelve si se ha pulsado una tecla
// \r es el retorno de carro, que si lo haces, vuelves a pintar la misma linea
// 27 es el codigo ascci del escape. si se pulsa se sale del bucle.
// Si se pulsa la j o la k se mueve la X para la izquierda y la derecha
// Si se pulsa la n o la m se dispara una bala para la izquierda o la derecha
// Cada cierto tiempo aparece un enemigo, en la izquierda o la dcha, que va hacia tu posicion, y si choca contigo te quita vida. Si le da una bala, muere el.
// Que aparezca un champiñon que te de puntos
// Mostrar el numero de vidas que te quedan, y los puntos que tienes, en la misma linea que el mapa.

// Dia 2 (esta version se entrega):
// Poder disparar varias balas. Usar un struct bala {int x; dir} y luego std::list <bala>
// Para recorrer la lista: for (auto it = balas.begin(); it != balas.end(); it++)
// Que aparezcan varios enemigos

// BUG con el tiempo de enemigo, tiene que haber tiempo aleatorio entre enemigos
// COMPRUEBA LOS CONST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Dia 3 (esta version se entrega):
// Organizar el codigo en clases, en distintos modulos, sin usar herencia.
// Clases enemigo, bala, jugador
// Clase gestor metereologico: cuando se pinta, se pregunta a esta clase que hay que pintar, ya que esta clase es la que gestiona internamente donde estan y el estado de las gotas
// Para imprimir las gotas, se pueden usar varios iconos:  gota "'", tocando el suelo ",", desapareciendo "."
// Usar pragma once

// Dia 4 (esta version se entrega):
// Grabar un video jugando al juego

#pragma warning(disable:4710)
#pragma warning(disable:4668)

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <list>

using namespace std;

#define ESC_KEY                   27
#define A_KEY                     'a'
#define D_KEY                     'd'
#define J_KEY                     'j'
#define L_KEY                     'l'
#define CONSOLE_WIDTH             1000
#define CONSOLE_HEIGHT            400
#define RANDOM_ENEMY_TIME         (rand() % 2 + 1) * 1000
#define RANDOM_MUSHROOM_TIME      (rand() % 7 + 1) * 1000       


enum dir {
	LEFT,
	RIGHT,
	NONE
};

// Para la version del dia 2, se permite crear un pequeño struct para hacer la lista de las balas y enemigos
struct object {
	int m_pos;
	dir m_dir;

	object(int pos, dir dir) {
		m_pos = pos;
		m_dir = dir;
	}
};

// Funcion que determina que enemigos han sido alcanzados en un frame del juego
void enemyReached(list<object>& bullets, list<object>& enemies, int& score, int& enemyTime) {
	for (auto itb = bullets.begin(); itb != bullets.end(); itb++) {
		for (auto ite = enemies.begin(); ite != enemies.end(); ite++) {
			if (itb->m_pos == ite->m_pos) {
				itb->m_pos    =  -10;
				ite->m_pos    =  -10;
				score         += 1;
				enemyTime     =  RANDOM_ENEMY_TIME;
			}
		}
	}
}

// Funcion que determina si el juegador ha sido alcanzado en un frame del juego
void playerReached(const int playerPos, list<object>& enemies, int& lives, int& enemyTime) {
	for (auto ite = enemies.begin(); ite != enemies.end(); ite++) {
		if (ite->m_pos == playerPos) {
			ite->m_pos    =  -10;
			lives         -= 1;
			enemyTime     =  RANDOM_ENEMY_TIME;
		}
	}
}

// Funcion que determina si en una posicion del mapa hay una bala en un frame del juego
dir isBullet(int pos, list<object>& bullets) {
	dir bulletDir = dir::NONE;
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		if (it->m_pos == pos) {
			bulletDir = it->m_dir;
		}
	}
	return bulletDir;
}

// Funcion que determina si en una posicion del mapa hay un enemigo en un frame del juego
bool isEnemy(int pos, list<object>& enemies) {
	bool isEne = false;
	for (auto ite = enemies.begin(); ite != enemies.end(); ite++) {
		if (ite->m_pos == pos) {
			isEne = true;;
		}
	}
	return isEne;
}

int main(){
	// Modificamos la dimension de la consola
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, TRUE); 

	// Si es negativa la posicion de un objeto: no existe.
	bool       escKeyPressed  = false;
	int	       maxPos         = 40;	
	int	       playerPos      = 20;
	int        score          = 0;
	int        lives          = 3;
	int        mushroomPos    = -1;
	int        maxBullets     = 3;
	int        maxEnemies     = 3;
	int        enemyTime      = RANDOM_ENEMY_TIME;
	int        mushroomTime   = RANDOM_MUSHROOM_TIME;
	list<object> bullets;
	list<object> enemies;

	//Pintamos las instrucciones
	printf("Movimiento: A y D. Disparo: J y K. Salir: ESC.\n\n\n");
		
	// Bucle del juego
	while ((!escKeyPressed) && (lives > 0)) {

		// Comprobamos que la bala mata al enemigo
		enemyReached(bullets, enemies, score, enemyTime);

		// Si hay balas, las movemos una posicion, y si se salen del mapa, las eliminamos de la lista
		auto itb = bullets.begin();
		while (itb != bullets.end()) {
			if (itb->m_dir == dir::LEFT) {
				itb->m_pos--;
			}
			else {
				itb->m_pos++;
			}
			if ((itb->m_pos < 1) || (itb->m_pos > maxPos)) {
				itb = bullets.erase(itb);
			}
			else {
				itb++;
			}
		}

		// Comprobamos que la bala mata al enemigo
		enemyReached(bullets, enemies, score, enemyTime);

		// Comprobamos que el enemigo mata al jugador
		playerReached(playerPos, enemies, lives, enemyTime);

		// Si esta el enemigo, avanza, si esta fuera del mapa, se elimina
		auto ite = enemies.begin();
		while (ite != enemies.end()) {
			if (ite->m_dir == dir::RIGHT) {
				ite->m_pos++;
			}
			else {
				ite->m_pos--;
			}
			if ((ite->m_pos > maxPos) || (ite->m_pos < 1)) {
				ite = enemies.erase(ite);
			}
			else {
				ite++;
			}
		}

		// Comprobamos que la bala mata al enemigo
		enemyReached(bullets, enemies, score, enemyTime);

		// Comprobamos que el enemigo mata al jugador
		playerReached(playerPos, enemies, lives, enemyTime);

		// Comprobamos si aparece el enemigo
		if ((enemyTime < 0) && (enemies.size() < maxEnemies)) {
			int random = (rand() % 2);
			if (random == 0) {
				bool firstPosEnemy = false;
				for (ite = enemies.begin(); ite != enemies.end(); ite++) {
					if (ite->m_pos == 1) {
						firstPosEnemy = true;
					}
				}
				if (!firstPosEnemy) {
					object enemy1(1, dir::RIGHT);
					enemies.push_back(enemy1);
				}
			}
			else {
				bool lastPosEnemy = false;
				for (ite = enemies.begin(); ite != enemies.end(); ite++) {
					if (ite->m_pos == maxPos) {
						lastPosEnemy = true;
					}
				}
				if (!lastPosEnemy) {
					object enemy1(maxPos, dir::LEFT);
					enemies.push_back(enemy1);
				}
			}
		}
		else {
			enemyTime -= 50;
		}	

		// Comprobamos si sale el champi
		if ((mushroomPos < 0) && (mushroomTime < 0)) {
			mushroomPos = (rand() % maxPos + 1);
		}
		else {
			mushroomTime -= 50;
		}

		// Comprobamos que el jugador recoge el champi
		if (playerPos == mushroomPos) {
			mushroomPos = -1;
			mushroomTime = RANDOM_MUSHROOM_TIME;
			score += 5;
		}

		// Comprobamos si se ha pulsado una tecla, y se comprueba cual
		if (_kbhit()) {
			switch (_getch()) {
			case ESC_KEY  : escKeyPressed = true;                                                                      break;
			case A_KEY    : if (playerPos > 1)               { playerPos--; }                                          break;
			case D_KEY    : if (playerPos < maxPos)          { playerPos++; }                                          break;
			case L_KEY    : if (bullets.size() < maxBullets) { bullets.push_back(object(playerPos + 1, dir::RIGHT)); } break;
			case J_KEY    : if (bullets.size() < maxBullets) { bullets.push_back(object(playerPos - 1, dir::LEFT)); }  break;
			}
		}

		// Pintamos el mapa
		printf("\r");		
		for (int i = 1; i <= maxPos; i++) {
			dir dirBala = isBullet(i, bullets);
			if      (i == playerPos)        { printf("X"); }
			else if (isEnemy(i, enemies))   { printf("@"); }
			else if (i == mushroomPos)      { printf("T"); }
			else if (dirBala == dir::RIGHT) { printf(">"); }
			else if (dirBala == dir::LEFT)  { printf("<"); }
			else                            { printf("_"); }		
		}

		// Pintamos las vidas y la puntuacion
		printf("     vidas: %i, puntuacion: %i", lives, score);
		Sleep(50);
	}

	// Fin de la partida.
	printf("\n\nPuntuacion final : %i\n", score);
	printf("Pulse intro para salir");
	getchar();
    return 0;
}