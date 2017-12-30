// Adrian Gonzalez Lopez
// Practica de Ingenieria de Software

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
// Herramienta gratuita para detectar memory leaks. 
// Para usarla, hay que instalar en el pc a compilar el "Visual Leak Detector" y descomentar esta linea
//#include <vld.h>

using namespace std;

#define ESC_KEY 27
#define A_KEY   'a'
#define D_KEY   'd'
#define J_KEY   'j'
#define L_KEY   'l'

int main()
{
	// Configuracion de la partida
	unsigned int     RANDOM_ENEMY_TIME    = (rand() % 4 + 1) * 100;
	unsigned int     RANDOM_MUSHROOM_TIME = (rand() % 7 + 1) * 1000;
	unsigned int     MAX_BULLETS          = 3;
	unsigned int     MAX_MAP              = 40;
	unsigned int     MAX_ENEMIES          = 3;
	int              score                = 0;
	int	             lives                = 3;
	int              mushroomScore        = 5;
	unsigned int     dropTimeToFall       = 1000;
	// Medidas de la ventana de la consola
	int              CONSOLE_WIDTH        = 600;
	int              CONSOLE_HEIGHT       = 400;

	// Modificamos la dimension de la consola
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, CONSOLE_WIDTH, CONSOLE_HEIGHT, TRUE);

	//Pintamos las instrucciones
	printf("\n\n");
	printf("Movimiento: A y D. Disparo: J y L. Salir: ESC.\n\n");
	printf("Solo puedes disparar tres balas de forma consecutiva. Cada muerte es 1 punto.\n");
	printf("Solo habra tres enemigos de forma concurrente.\n");
	printf("Coge el champinon para ganar 5 puntos.\n\n");
	printf("Pulse intro para iniciar la partida.\n");
	getchar();
	printf("\n\n");

	// Creamos una instancia de World
	World world(
		RANDOM_ENEMY_TIME,
	    RANDOM_MUSHROOM_TIME,
	    MAX_BULLETS,
	    MAX_MAP,
	    MAX_ENEMIES,
	    score,
	    lives,
	    mushroomScore,
	    dropTimeToFall);

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

		// Movemos los enemigos
		world.moveEnemies();

		// Creamos enemigos nuevos si toca
		world.createEnemy();

		// Aparece el champiñon si toca
		world.showMushroom();

		// Creamos gotas
		world.createDrop();

		// Actualizamos el estado de las gotas
		world.updateDrops();

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