/*
 * Mecanicas.cpp
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier Brizuela
 *      Aquí se programa la jugabilidad del programa, la manera en la que se determina si alguien ha ganado la partida y la acción de colocar fichas.
 */

#include "Mecanicas.h"
#include "Jugador.h"
#include "BD.h"
#include <stdbool.h>
#include <stdio.h>

#include "IA.h"

int filaLibre(Ficha **tablero, int columna) {
	int i = 0;
	while (tablero[columna][i].getTipo() != 0) {
		i++;
	}
	return i;
}
bool colocarFicha(Ficha **tablero, int jugador, int columna) {
	if (filaLibre(tablero, columna) > FILAS - 1) {
		return false;
	}
	tablero[columna][filaLibre(tablero, columna)].setTipo(jugador);
	return true;
}
int comprobarVertical(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].getTipo();
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna][fila - 1 - arriba].getTipo() == jugador) {
		arriba++;
		if (fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna][fila + 1 + abajo].getTipo() == jugador) {
		abajo++;
		if (fila + 1 + abajo > FILAS - 1) {
			break;
		}
	}
	return 1 + arriba + abajo;
}
int comprobarHorizontal(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].getTipo();
	int izquierda = 0;
	int derecha = 0;
	while (tablero[columna - 1 - izquierda][fila].getTipo() == jugador) {
		izquierda++;
		if (columna - 1 - izquierda < 0) {
			break;
		}
	}
	while (tablero[columna + 1 + derecha][fila].getTipo() == jugador) {
		derecha++;
		if (columna + 1 + derecha > COLUMNAS - 1) {
			break;
		}
	}
	return 1 + derecha + izquierda;
}

int comprobarDiagonalIzq(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].getTipo();
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna - arriba - 1][fila - 1 - arriba].getTipo() == jugador) {
		arriba++;
		if (columna - arriba - 1 < 0 || fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna + abajo + 1][fila + 1 + abajo].getTipo() == jugador) {
		abajo++;
		if (columna + abajo + 1 > COLUMNAS - 1
				|| fila + 1 + abajo > FILAS - 1) {
			break;
		}
	}
	return 1 + arriba + abajo;
}
int comprobarDiagonalDer(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].getTipo();
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna + 1 + arriba][fila - 1 - arriba].getTipo() == jugador) {
		arriba++;
		if (columna + arriba + 1 > COLUMNAS - 1 || fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna - 1 - abajo][fila + 1 + abajo].getTipo() == jugador) {
		abajo++;
		if (columna - abajo - 1 < 0 || fila + 1 + abajo > FILAS - 1) {
			break;
		}
	}
	return 1 + arriba + abajo;
}

int comprobarVictoria(Ficha **tablero, int objetivo) {
	int i;
	for (i = 0; i < COLUMNAS; i++) {
		int j;
		for (j = 0; j < FILAS; ++j) {
			if (!((i == 0 && (j == 0 || j == FILAS - 1))
					|| (i == COLUMNAS - 1 && (j == 0 || j == FILAS - 1)))
					&& tablero[i][j].getTipo() != 0) {
				if (i == 0 || i == COLUMNAS - 1) {
					if (comprobarVertical(tablero, i, j) > objetivo - 1) {
						return tablero[i][j].getTipo();
					}
				} else if (j == 0 || j == FILAS - 1) {
					if (comprobarHorizontal(tablero, i, j) > objetivo - 1) {
						return tablero[i][j].getTipo();
					}
				} else {
					if (comprobarHorizontal(tablero, i, j) > objetivo - 1
							|| comprobarVertical(tablero, i, j) > objetivo - 1
							|| comprobarDiagonalDer(tablero, i, j)
									> objetivo - 1
							|| comprobarDiagonalIzq(tablero, i, j)
									> objetivo - 1) {
						return tablero[i][j].getTipo();
					}
				}
			}

		}
	}
	return 0;
}

int numeroDeVictorias(Ficha **tablero, int objetivo) {
	int n = 0;
	int i;
	for (i = 0; i < COLUMNAS; i++) {
		int j;
		for (j = 0; j < FILAS; ++j) {
			if (!((i == 0 && (j == 0 || j == FILAS - 1))
					|| (i == COLUMNAS - 1 && (j == 0 || j == FILAS - 1)))
					&& tablero[i][j].getTipo() != 0) {
				if (i == 0 || i == COLUMNAS - 1) {
					if (comprobarVertical(tablero, i, j) > objetivo - 1) {
						n++;
					}
				} else if (j == 0 || j == FILAS - 1) {
					if (comprobarHorizontal(tablero, i, j) > objetivo - 1) {
						n++;
					}
				} else {
					if (comprobarHorizontal(tablero, i, j) > objetivo - 1
							|| comprobarVertical(tablero, i, j) > objetivo - 1
							|| comprobarDiagonalDer(tablero, i, j)
									> objetivo - 1
							|| comprobarDiagonalIzq(tablero, i, j)
									> objetivo - 1) {
						n++;
					}
				}
			}

		}
	}
	return n;
}

char inicioSesion() {
	cout << "1. Registrarse" << endl;
	cout << "2. Iniciar sesión" << endl;
	cout << "9. Salir" << endl;
	cout << "\n" << endl;
	cout << "Opción: " << endl;

	char linea;
	cin >> linea;

	return linea;
}



char menuInicio() {
	cout << "1. Jugar partida" << endl;
	cout << "2. Ver estadisticas" << endl;
	cout << "9. Para salir" << endl;
	cout << "\n" << endl;
	cout << "Opción: " << endl;

	char linea[2];
	cin >> linea;

	return *linea;
}

bool empate(Ficha **tablero) {
	for (int n = 0; n < COLUMNAS; n++) {
		if (filaLibre(tablero, n) < FILAS) {
			return false;
		}
	}
	return true;
}

void jugarPartida(Ficha **tablero, bool contraIA, Jugador jugador, Jugador jugador2, sqlite3 *db) {

	limpiar(tablero);
	bool juegaJug1 = true;
	int numeroJug;
	do {

		if (juegaJug1) {
			numeroJug = 1;
		} else {
			numeroJug = 2;
		}
		int columna;
		if (!contraIA || juegaJug1) {
			do {
				if (columna < 1 || columna > COLUMNAS) {
					cout
							<< "\nEl numero de columna introducido no es valido. Vuelve a intentarlo."
							<< endl;
				}

				visualizarTablero(tablero);

				cout << "Es el turno de Jugador " << numeroJug << "\n" << endl;
				cout << "En que columna quieres poner tu ficha?\n" << endl;

				cin >> columna;

			} while (columna < 1 || columna > COLUMNAS);

			if (colocarFicha(tablero, numeroJug, columna - 1)) {

				juegaJug1 = !juegaJug1;
			}
		} else {
			//JuegaIA
			int colocado = eleccionIA(tablero);
			colocarFicha(tablero, numeroJug, colocado);
			cout << "La IA ha coloca en la columna " << colocado + 1 << "."
					<< endl;
			juegaJug1 = !juegaJug1;
		}

	} while (comprobarVictoria(tablero, OBJETIVO) == 0 && !empate(tablero));
	visualizarTablero(tablero);
	if (comprobarVictoria(tablero, OBJETIVO) != 0) {

		if (comprobarVictoria(tablero, OBJETIVO) == 1) {
			sumarVictoria(db, jugador);
			cout << "Has ganado " << jugador.getEMail()	<< ". Felicidades!\n" << endl;

		} else if (comprobarVictoria(tablero, OBJETIVO) == 2) {
			sumarVictoria(db, jugador2);
			cout << "Has ganado " << jugador2.getEMail()	<< ". Felicidades!\n" << endl;
		}
	} else {
		cout << "Habeis empatado." << endl;
	}

}
