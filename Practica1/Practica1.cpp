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

using namespace std;

#define ESC_KEY 27
#define A_KEY   'a'
#define D_KEY   'd'
#define J_KEY   'j'
#define L_KEY   'l'

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
	printf("Movimiento: A y D. Disparo: J y L. Salir: ESC.\n\n");
	printf("Solo puedes disparar tres balas de forma consecutiva. Cada muerte es 1 punto.\n");
	printf("Solo habra tres enemigos de forma concurrente.\n");
	printf("Coge el chamiñon para ganar 5 puntos.\n\n");
	printf("Pulse intro para iniciar la partida.\n");
	getchar();
	printf("\n\n");

	// Creamos una instancia de World
	// La clase World indorpora tanto la gestion meteorologica, como la gestion de los objetos que afectan a la jugabilidad
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