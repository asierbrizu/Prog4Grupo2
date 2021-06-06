/*
 * Nanami.cpp
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier Brizuela
 */
#include "IA.h"
#include <time.h>

Ficha** clonarTablero(Ficha **tablero) {
	Ficha **copia = new Ficha*[COLUMNAS];
	int i;
	for (i = 0; i < COLUMNAS; ++i) {
		copia[i] = new Ficha[FILAS];
	}

	for (int i = 0; i < COLUMNAS; ++i) {
		for (int j = 0; j < FILAS; ++j) {
			copia[i][j].setTipo(tablero[i][j].getTipo());
		}
	}
	return copia;
}

int eleccionIA(Ficha **tablero) {

	//1. Comprueba victoria inminente para IA.
	if (comprobrobarVictoriaInminente(tablero, 2, OBJETIVO)) {
		return numVictoriaInminente(tablero, 2, OBJETIVO);
	}

	//2. Impide victoria inminente para Jugador.
	if (comprobrobarVictoriaInminente(tablero, 1, OBJETIVO)) {
		return numVictoriaInminente(tablero, 1, OBJETIVO);
	}

	//3. Comprueba victorias próximas para IA.
	for (int n = 0; n < COLUMNAS; n++) {
		bool seRealiza = false;
		int jugada = -1;
		Ficha **posibilidad = clonarTablero(tablero);
		colocarFicha(posibilidad, 2, n);
		if (!comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO)) {
			if (comprobrobarVictoriaInminente(posibilidad, 2, OBJETIVO)) {
				int jugadaJugador = numVictoriaInminente(posibilidad, 2,
						OBJETIVO);
				colocarFicha(posibilidad, 1,
						numVictoriaInminente(posibilidad, 2, OBJETIVO));
				if (comprobrobarVictoriaInminente(posibilidad, 2, OBJETIVO)) {
					seRealiza = true;
					jugada = n;
				}
			}
		}

		liberarTablero(posibilidad);
		if (seRealiza) {
			return jugada;
		}
	}

	//4 Intentar alinear 3
	for (int n = 0; n < COLUMNAS; n++) {
		Ficha **posibilidad = clonarTablero(tablero);
		bool seRealiza = false;
		int jugada = -1;
		colocarFicha(posibilidad, 2, n);

		if (numeroDeVictorias(posibilidad, OBJETIVO - 1)
				> numeroDeVictorias(tablero, OBJETIVO - 1)
				&& !comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO)
				&& comprobrobarVictoriaInminente(posibilidad, 2, OBJETIVO)
				&& !existePeligro(tablero, n)) {
			seRealiza = true;
			jugada = n;
		}
		liberarTablero(posibilidad);
		if (seRealiza) {
			return jugada;
		}
	}

	//5 Evitar alinear 3
	for (int n = 0; n < COLUMNAS; n++) {
		Ficha **posibilidad = clonarTablero(tablero);
		bool seRealiza = false;
		int jugada = -1;
		colocarFicha(posibilidad, 1, n);

		bool masAlineaciones = numeroDeVictorias(posibilidad, OBJETIVO - 1)
				> numeroDeVictorias(tablero, OBJETIVO - 1);
		colocarFicha(posibilidad, 2, numVictoriaInminente(posibilidad, 1, 4));

		if (masAlineaciones
				&& !comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO)
				&& !derrotaProxima(tablero, n) && !existePeligro(tablero, n)) {
			seRealiza = true;
			jugada = n;
		}
		liberarTablero(posibilidad);
		if (seRealiza) {
			return jugada;
		}
	}

	//6. Evita victorias próximas para Jugador.
	srand(time(NULL));
	for (int c = 0; c < COLUMNAS * 10; c++) {

		int n = rand() % COLUMNAS;

		if (!existePeligro(tablero, n) && filaLibre(tablero, n) < FILAS) {
			return n;
		}
	}

	//7 Jugada desesperada
	for (int libre = 0; libre < COLUMNAS; libre++) {
		if (filaLibre(tablero, libre) < FILAS) {
			return libre;
		}
	}

	return 0;
}
bool comprobrobarVictoriaInminente(Ficha **tablero, int jugador, int objetivo) {
	bool gana = false;
	for (int n = 0; n < COLUMNAS; n++) {

		Ficha **posibilidad = clonarTablero(tablero);
		colocarFicha(posibilidad, jugador, n);
		if (comprobarVictoria(posibilidad, objetivo) == jugador) {
			gana = true;

		}
		liberarTablero(posibilidad);

	}
	return gana;
}

int numVictoriaInminente(Ficha **tablero, int jugador, int objetivo) {
	for (int n = 0; n < COLUMNAS; n++) {
		bool seRealiza = false;
		int jugada = -1;
		Ficha **posibilidad = clonarTablero(tablero);
		colocarFicha(posibilidad, jugador, n);
		if (comprobarVictoria(posibilidad, objetivo) == jugador) {
			seRealiza = true;
			jugada = n;
		}
		liberarTablero(posibilidad);
		if (seRealiza) {
			return jugada;
		}
	}
	return 0;
}

void liberarTablero(Ficha **tablero) {
	for (int i = 0; i < COLUMNAS; i++) {
		delete[] tablero[i];
	}
	delete[] tablero;
}
bool derrotaProxima(Ficha **tablero, int jugada) {
	Ficha **posibilidad = clonarTablero(tablero);
	colocarFicha(posibilidad, 2, jugada);
	return comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO);
}
bool existePeligro(Ficha **tablero, int jugada) {

	bool seRealiza = true;
	Ficha **posibilidad = clonarTablero(tablero);
	colocarFicha(posibilidad, 2, jugada);

	if (!comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO)) {

		for (int m = 0; m < COLUMNAS; m++) {

			Ficha **posibilidad2 = clonarTablero(posibilidad);
			colocarFicha(posibilidad2, 1, m);
			if (comprobrobarVictoriaInminente(posibilidad2, 1, OBJETIVO)) {

				colocarFicha(posibilidad2, 2,
						numVictoriaInminente(posibilidad2, 1, OBJETIVO));
				if (comprobrobarVictoriaInminente(posibilidad2, 1, OBJETIVO)) {

					seRealiza = false;
				}
			}

			liberarTablero(posibilidad2);

		}
	} else {

		seRealiza = false;
	}

	liberarTablero(posibilidad);

	return !seRealiza;

}
