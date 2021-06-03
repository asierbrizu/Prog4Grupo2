/*
 * Mecanicas.c
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aquí se programa la jugabilidad del programa, la manera en la que se determina si alguien ha ganado la partida y la acción de colocar fichas.
 */
#include "Tablero.h"
#include "Mecanicas.h"
#include <stdbool.h>
#include <stdio.h>

void clearIfNeeded(char *str, int max_line) {
	if ((strlen(str) == max_line - 1) && (str[max_line - 2] != '\n'))
		while (getchar() != '\n')
			;
}

int filaLibre(Ficha **tablero, int columna) {
	int i = 0;
	while (tablero[columna][i].tipo != 0) {
		i++;
	}
	return i;
}
bool colocarFicha(Ficha **tablero, int jugador, int columna) {
	if (filaLibre(tablero, columna) > 5) {
		printf("\nLa columna seleccionada esta llena.\n");
		return false;
	}
	tablero[columna][filaLibre(tablero, columna)].tipo = jugador;
	return true;
}
int comprobarVertical(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].tipo;
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna][fila - 1 - arriba].tipo == jugador) {
		arriba++;
		if (fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna][fila + 1 + abajo].tipo == jugador) {
		abajo++;
		if (fila + 1 + abajo > 5) {
			break;
		}
	}
	return 1 + arriba + abajo;
}
int comprobarHorizontal(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].tipo;
	int izquierda = 0;
	int derecha = 0;
	while (tablero[columna - 1 - izquierda][fila].tipo == jugador) {
		izquierda++;
		if (columna - 1 - izquierda < 0) {
			break;
		}
	}
	while (tablero[columna + 1 + derecha][fila].tipo == jugador) {
		derecha++;
		if (columna + 1 + derecha > 6) {
			break;
		}
	}
	return 1 + derecha + izquierda;
}

int comprobarDiagonalIzq(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].tipo;
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna - arriba - 1][fila - 1 - arriba].tipo == jugador) {
		arriba++;
		if (columna - arriba - 1 < 0 || fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna + abajo + 1][fila + 1 + abajo].tipo == jugador) {
		abajo++;
		if (columna + arriba + 1 > 6 || fila + 1 + arriba > 5) {
			break;
		}
	}
	return 1 + arriba + abajo;
}
int comprobarDiagonalDer(Ficha **tablero, int columna, int fila) {
	int jugador = tablero[columna][fila].tipo;
	int arriba = 0;
	int abajo = 0;
	while (tablero[columna + 1 + arriba][fila - 1 - arriba].tipo == jugador) {
		arriba++;
		if (columna + arriba + 1 > 6 || fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna - 1 - abajo][fila + 1 + abajo].tipo == jugador) {
		abajo++;
		if (columna - arriba - 1 < 0 || fila + 1 + arriba > 5) {
			break;
		}
	}
	return 1 + arriba + abajo;
}

int comprobarVictoria(Ficha **tablero) {
	int i;
	for (i = 0; i < 7; i++) {
		int j;
		for (j = 0; j < 6; ++j) {
			if (!((i == 0 && (j == 0 || j == 5))
					|| (i == 6 && (j == 0 || j == 5)))
					&& tablero[i][j].tipo != 0) {
				if (i == 0 || i == 6) {
					if (comprobarVertical(tablero, i, j) > 3) {
						//printf("\nGanador por vertical en %i %i",i,j);
						return tablero[i][j].tipo;
					}
				} else if (j == 0 || j == 5) {
					if (comprobarHorizontal(tablero, i, j) > 3) {
						//printf("\nGanador por horizontal en %i %i",i,j);
						return tablero[i][j].tipo;
					}
				} else {
					if (comprobarHorizontal(tablero, i, j) > 3
							|| comprobarVertical(tablero, i, j) > 3
							|| comprobarDiagonalDer(tablero, i, j) > 3
							|| comprobarDiagonalIzq(tablero, i, j) > 3) {
						//printf("\nGanador en %i %i",i,j);
						return tablero[i][j].tipo;
					}
				}
			}

		}
	}
	return 0;
}

char inicioSesion(){
	printf("\n1. Registrarse\n");
	printf("\n2. Iniciar sesión\n");
	printf("\n9. Salir\n");
	printf("\n");
	printf("Opción: ");
	fflush(stdout);
	char linea[2];
	fgets(linea, 2, stdin);
	clearIfNeeded(linea, 2);
	return *linea;
}

char menuInicio() {
	printf("\n1. Jugar partida\n");
	printf("2. Ver estadisticas\n");

	printf("9. Para salir\n");
	printf("\n");
	printf("Opción: ");
	fflush(stdout);
	char linea[2];
	fgets(linea, 2, stdin);
	clearIfNeeded(linea, 2);
	return *linea;
}

void jugarPartida(Ficha **tablero) {
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
		do {
			if (columna < 1 || columna > 7) {
				printf(
						"\nEl numero de columna introducido no es valido. Vuelve a intentarlo.");
			}
			visualizarTablero(tablero);
			printf("Es el turno de Jugador %i\n", numeroJug);
			printf("En que columna quieres poner tu ficha?\n");
			fflush(stdout);
			char linea[2];
			fgets(linea, 2, stdin);
			clearIfNeeded(linea, 2);
			columna = *linea - '0';
		} while (columna < 1 || columna > 7);
		if (colocarFicha(tablero, numeroJug, columna - 1)) {
			juegaJug1 = !juegaJug1;
		}
	} while (comprobarVictoria(tablero) == 0);
	visualizarTablero(tablero);
	printf("Ha ganado el jugador %i. Felicidades!\n",
			comprobarVictoria(tablero));

}
