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
		cout << "Colocando en primer caso" << endl;
		return numVictoriaInminente(tablero, 2, OBJETIVO);
	}

//2. Impide victoria inminente para Jugador.
	if (comprobrobarVictoriaInminente(tablero, 1, OBJETIVO)) {
		cout << "Colocando en segundo caso" << endl;
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
					cout << "Se cree que si IA pone en " << n
							<< "(columnas 0-7), entonces jugador tendría que poner en "
							<< jugadaJugador
							<< ", lo que hace que cuando IA pone en "
							<< numVictoriaInminente(posibilidad, 2, OBJETIVO)
							<< " gana la partida." << endl;
					seRealiza = true;
					jugada = n;
				}
			}
		}

		liberarTablero(posibilidad);
		if (seRealiza) {
			cout << "Colocando en tercer caso" << endl;
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
			cout << "Colocando en cuarto caso" << endl;
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
				&& !derrotaProxima(tablero, n)
				&& !existePeligro(tablero, n)) {
			seRealiza = true;
			jugada = n;
		}
		liberarTablero(posibilidad);
		if (seRealiza) {
			cout << "Colocando en quinto caso" << endl;
			return jugada;
		}
	}

//6. Evita victorias próximas para Jugador.
	srand(time(NULL));
	for (int c = 0; c < COLUMNAS * 10; c++) {

		int n = rand() % COLUMNAS;

		if (!existePeligro(tablero, n) && filaLibre(tablero, n) < FILAS) {
			cout << "Colocando en sexto caso" << endl;
			return n;
		}
	}

//7 Jugada desesperada
	for (int libre = 0; libre < COLUMNAS; libre++) {
		if (filaLibre(tablero, libre) < FILAS) {
			cout << "Colocando en septimo caso" << endl;
			return libre;
		}
	}

	cout << "Colocando en error caso" << endl;
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

	cout << "Iniciando comprobación de peligro en jugada " << jugada << endl;
	bool seRealiza = true;
	Ficha **posibilidad = clonarTablero(tablero);
	colocarFicha(posibilidad, 2, jugada);

	if (!comprobrobarVictoriaInminente(posibilidad, 1, OBJETIVO)) {
		cout
				<< "Se ha comprobado que no hay victoria inminente al colocarla ahi"
				<< endl;
		cout << "Se van a realizar simulaciones" << endl;
		for (int m = 0; m < COLUMNAS; m++) {
			cout << "Simulacion de la columna " << m << endl;
			Ficha **posibilidad2 = clonarTablero(posibilidad);
			colocarFicha(posibilidad2, 1, m);
			if (comprobrobarVictoriaInminente(posibilidad2, 1, OBJETIVO)) {
				cout << "Habia victoria inminente para Jugador" << endl;
				colocarFicha(posibilidad2, 2,
						numVictoriaInminente(posibilidad2, 1, OBJETIVO));
				if (comprobrobarVictoriaInminente(posibilidad2, 1, OBJETIVO)) {
					cout << "Colocar ficha no habria resuelto el problema"
							<< endl;
					seRealiza = false;
				}
			}

			liberarTablero(posibilidad2);

		}
	} else {
		cout
				<< "Se ha comprobado que con la jugada habia victoria inminente para Jugador"
				<< endl;
		seRealiza = false;
	}

	liberarTablero(posibilidad);
	if (seRealiza) {
		cout << "Se determina que la jugada NO es peligrosa" << endl;
	} else {

		cout << "Se determina que la jugada SI es peligrosa" << endl;
	}

	return !seRealiza;

}
