// Adrian Gonzalez Lopez
// Practica 1 de Ingenieria de Software

// Usar printf para imprimir
// Kbhit() te devuelve si se ha pulsado una tecla
// \r es el retorno de carro, que si lo haces, vuelves a pintar la misma linea
// 27 es el codigo ascci del escape. si se pulsa se sale del bucle.
// Si se pulsa la j o la k se mueve la X para la izquierda y la derecha
// Si se pulsa la n o la m se dispara una bala para la izquierda o la derecha
// Cada cierto tiempo aparece un enemigo, en la izquierda o la dcha, que va hacia tu posicion, y si choca contigo te quita vida. Si le da una bala, muere el.
// Que aparezca un champiñon que te de puntos
// Mostrar el numero de vidas que te quedan, y los puntos que tienes, en la misma linea que el mapa.
// Añadido por mi: Cada vez que dispares el mapa se reduce, para darle dificultad.

#pragma warning(disable:4710)
#pragma warning(disable:4668)

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>

#define ESC_KEY 27
#define J_KEY 'j'
#define K_KEY 'k'
#define M_KEY 'm'
#define N_KEY 'n'
#define TIEMPO_ALEATORIO_ENEMIGO (rand() % 3 + 1) * 1000
#define TIEMPO_ALEATORIO_CHAMPI  (rand() % 7 + 1) * 1000

enum dir{
	IZQ = true,
	DCHA = false
};

void enemigoAlcanzado(int *posBala, int *posEnemigo, int *puntuacion, int *tiempoEnemigo, int *posMax, int *posX, int *posChampi) {
	if ((*posBala != -1) && (*posEnemigo != -1) && (*posBala == *posEnemigo)) {
		*posEnemigo = -1;
		*posBala = -1;
		*puntuacion += 1;
		*tiempoEnemigo = TIEMPO_ALEATORIO_ENEMIGO;
		if (*posMax > 5) {
			*posMax -= 2;
			while (*posX > *posMax) {
				*posX -= 1;
			}
			while (*posChampi > *posMax) {
				*posChampi -= 1;
			}
		}
	}
}

void jugadorAlcanzado(const int posX, int *posEnemigo, int *vidas, int *tiempoEnemigo) {
	if ((posEnemigo > 0) && (*posEnemigo == posX)) {
		*posEnemigo = -1;
		*vidas -= 1;
		*tiempoEnemigo = TIEMPO_ALEATORIO_ENEMIGO;
	}
}

int main(){

	// Modificamos la dimension de la consola
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1000, 400, TRUE); 

	// Si es negativa la posicion: no existen.
	int	 posMax         = 40;	
	int	 posX           = 20;
	int  posBala        = -1;
	bool dirBala        = dir::DCHA;
	bool escKeyPressed  = false;
	int  tiempoEnemigo  = TIEMPO_ALEATORIO_ENEMIGO;
	int  posEnemigo     = -1;
	bool dirEnemigo     = dir::DCHA;
	int  puntuacion     = 0;
	int  vidas          = 3;
	int  posChampi      = -1;
	int  tiempoChampi   = TIEMPO_ALEATORIO_CHAMPI;
		
	//Bucle del juego
	while ((!escKeyPressed) && (vidas > 0)) {
		// Si hay bala, la movemos una posicion
		if ((posBala > 0) && (posBala < posMax)) {
			if (dirBala) {
				posBala--;
			}
			else {
				posBala++;
			}
		}
		else {
			posBala = -1;
		}

		// Comprobamos que el enemigo mata al jugador
		jugadorAlcanzado(posX, &posEnemigo, &vidas, &tiempoEnemigo);

		// Comprobamos que la bala mata al enemigo
		enemigoAlcanzado(&posBala, &posEnemigo, &puntuacion, &tiempoEnemigo, &posMax, &posX, &posChampi);

		// Si esta el enemigo, avanza
		if (posEnemigo > 0) {
			if (dirEnemigo == dir::DCHA) {
				posEnemigo++;
			}
			else {
				posEnemigo--;
			}
		}

		// Comprobamos que la bala mata al enemigo
		enemigoAlcanzado(&posBala, &posEnemigo, &puntuacion, &tiempoEnemigo, &posMax, &posX, &posChampi);

		// Comprobamos que el enemigo mata al jugador
		jugadorAlcanzado(posX, &posEnemigo, &vidas, &tiempoEnemigo);

		// Comprobamos si aparece el enemigo
		if ((tiempoEnemigo < 0) && (posEnemigo < 0)) {
			int random = (rand() % 2);
			if (random == 0) {
				posEnemigo = 1;
				dirEnemigo = dir::DCHA;
			}
			else {
				posEnemigo = posMax;
				dirEnemigo = dir::IZQ;
			}
		}
		else if (posEnemigo < 0) {
			tiempoEnemigo -= 50;
		}	

		// Comprobamos si sale el champi
		if ((posChampi < 0) && (tiempoChampi < 0)) {
			posChampi = (rand() % posMax + 1);
		}
		else {
			tiempoChampi -= 50;
		}

		// Comprobamos que el jugador recoge el champi
		if (posX == posChampi) {
			posChampi = -1;
			tiempoChampi = TIEMPO_ALEATORIO_CHAMPI;
			puntuacion += 5;
		}

		// Comprobamos si se ha pulsado una tecla, y se comprueba cual
		if (_kbhit()) {
			switch (_getch()) {
			case ESC_KEY:
				escKeyPressed = true;
				break;
			case J_KEY:
				if (posX > 1) {
					posX--;
				}
				break;
			case K_KEY:
				if (posX < posMax) {
					posX++;
				}
				break;
			case M_KEY:
				if (posBala < 0) {
					posBala = posX + 1;
					dirBala = dir::DCHA;
				}				
				break;
			case N_KEY:
				if (posBala < 0) {
					posBala = posX - 1;
					dirBala = dir::IZQ;
				}
				break;
			}
		}

		// Pintamos el mapa
		printf("\r");		
		for (int i = 1; i <= posMax; i++) {
			if (i == posX) {
				printf("X");
			}
			else if (i == posBala) {
				if (dirBala) {
					printf("<");
				}
				else {
					printf(">");
				}
			}
			else if (i == posEnemigo) {
				printf("@");
			}
			else if (i == posChampi) {
				printf("T");
			}
			else {
				printf("_");
			}			
		}

		// Pintamos las vidas y la puntuacion
		printf("     vidas: %i, puntuacion: %i. Mov: J/K. Disparo: N/M. Salir ESC.", vidas, puntuacion);
		Sleep(50);
	}

	// Fin de la partida
	printf("\n\nPuntuacion final : %i\n", puntuacion);
	printf("Pulse intro para salir");
	getchar();
    return 0;
}