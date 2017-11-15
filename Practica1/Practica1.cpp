// Adrian Gonzalez Lopez
// Practica 1 de Ingenieria de Software

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
// Dia 2:
// Añadir lluvia, que sea un nuevo icono que aparezca de forma aleatoria
// Poder disparar varias balas. Usar un struct bala {int x; dir} y luego std::list <bala> balas; balas.pushback(bala1)
// Para recorrer la lista: for (auto it = balas.begin(); it != balas.end(); it++)
// Que aparezcan varios enemigos

#pragma warning(disable:4710)
#pragma warning(disable:4668)

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <list>

#define ESC_KEY                   27
#define A_KEY                     'a'
#define D_KEY                     'd'
#define J_KEY                     'j'
#define L_KEY                     'l'
#define TIEMPO_ALEATORIO_ENEMIGO  (rand() % 3 + 1) * 1000
#define TIEMPO_ALEATORIO_CHAMPI   (rand() % 7 + 1) * 1000
#define TAMAÑO_MINIMO_MAPA        5
#define ANCHO_CONSOLA             1000
#define ALTO_CONSOLA              400

using namespace std;

enum dir {
	IZQ,
	DCHA,
	NONE
};

struct bala {
	int pos;
	dir direccion;

	bala(int pos, dir direccion) {
		this->pos       = pos;
		this->direccion = direccion;
	}
};

void enemigoAlcanzado(list<bala> balas, int *posEnemigo, int *puntuacion, int *tiempoEnemigo) {
	for (auto it = balas.begin(); it != balas.end(); it++) {
		if ((it->pos != -1) && (*posEnemigo != -1) && (it->pos == *posEnemigo)) {
			it->pos = -1;
			*posEnemigo = -1;
			*puntuacion += 1;
			*tiempoEnemigo = TIEMPO_ALEATORIO_ENEMIGO;
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

dir hayBala(int pos, list<bala> balas) {
	dir bala = dir::NONE;
	for (auto it = balas.begin(); it != balas.end(); it++) {
		if (it->pos == pos) {
			bala = it->direccion;
		}
	}
	return bala;
}

int main(){

	// Modificamos la dimension de la consola
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, ANCHO_CONSOLA, ALTO_CONSOLA, TRUE); 

	//Pintamos las instrucciones
	printf("Movimiento: A y D. Disparo: J y K. Salir: ESC.\n\n\n");

	// Si es negativa la posicion: no existen.
	int	       posMax         = 40;	
	int	       posX           = 20;
	bool       escKeyPressed  = false;
	int        tiempoEnemigo  = TIEMPO_ALEATORIO_ENEMIGO;
	int        posEnemigo     = -1;
	dir        dirEnemigo     = dir::DCHA;
	int        puntuacion     = 0;
	int        vidas          = 3;
	int        posChampi      = -1;
	int        tiempoChampi   = TIEMPO_ALEATORIO_CHAMPI;
	int        NumMaxBalas    = 3;
	list<bala> balas;
		
	//Bucle del juego
	while ((!escKeyPressed) && (vidas > 0)) {

		// Comprobamos que la bala mata al enemigo
		enemigoAlcanzado(balas, &posEnemigo, &puntuacion, &tiempoEnemigo);

		// Si hay balas, las movemos una posicion, y si se salen del mapa, las eliminamos de la lista
		auto it = balas.begin();
		while (it != balas.end()) {
			if (it->direccion == dir::IZQ) {
				it->pos--;
				if (it->pos == 0) {
					it = balas.erase(it);
				}
				else {
					it++;
				}
			}
			else {
				it->pos++;
				if (it->pos > posMax) {
					it = balas.erase(it);
				}
				else {
					it++;
				}
			}
		}

		// Comprobamos que la bala mata al enemigo
		enemigoAlcanzado(balas, &posEnemigo, &puntuacion, &tiempoEnemigo);

		// Comprobamos que el enemigo mata al jugador
		jugadorAlcanzado(posX, &posEnemigo, &vidas, &tiempoEnemigo);

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
		enemigoAlcanzado(balas, &posEnemigo, &puntuacion, &tiempoEnemigo);

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
			case A_KEY:
				if (posX > 1) {
					posX--;
				}
				break;
			case D_KEY:
				if (posX < posMax) {
					posX++;
				}
				break;
			case L_KEY:
				if (balas.size() < NumMaxBalas) {
					bala bala1 (posX + 1, dir::DCHA);
					balas.push_back(bala1);
				}			
				break;
			case J_KEY:
				if (balas.size() < NumMaxBalas) {
					bala bala1(posX - 1, dir::IZQ);
					balas.push_back(bala1);
				}
				break;
			}
		}

		// Pintamos el mapa
		printf("\r");		
		for (int i = 1; i <= posMax; i++) {
			dir dirBala = hayBala(i, balas);
			if (i == posX) {
				printf("X");
			}
			else if (i == posEnemigo) {
				printf("@");
			}
			else if (i == posChampi) {
				printf("T");
			}
			else if (dirBala == dir::DCHA) {
				printf(">");
			}
			else if (dirBala == dir::IZQ) {
				printf("<");
			}
			else {
				printf("_");
			}		
		}

		// Pintamos las vidas y la puntuacion
		printf("     vidas: %i, puntuacion: %i", vidas, puntuacion);
		Sleep(50);
	}

	// Fin de la partida
	printf("\n\nPuntuacion final : %i\n", puntuacion);
	printf("Pulse intro para salir");
	getchar();
    return 0;
}