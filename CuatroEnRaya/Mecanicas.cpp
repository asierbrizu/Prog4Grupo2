/*
 * Mecanicas.c
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aquí se programa la jugabilidad del programa, la manera en la que se determina si alguien ha ganado la partida y la acción de colocar fichas.
 */

#include "Mecanicas.h"
#include <stdbool.h>
#include <stdio.h>


int filaLibre(Ficha **tablero, int columna) {
	int i = 0;
	while (tablero[columna][i].getTipo() != 0) {
		i++;
	}
	return i;
}
bool colocarFicha(Ficha **tablero, int jugador, int columna) {
	if (filaLibre(tablero, columna) > 5) {
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
		if (fila + 1 + abajo > 5) {
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
		if (columna + 1 + derecha > 6) {
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
		if (columna + abajo + 1 > 6 || fila + 1 + abajo > 5) {
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
		if (columna + arriba + 1 > 6 || fila - 1 - arriba < 0) {
			break;
		}
	}
	while (tablero[columna - 1 - abajo][fila + 1 + abajo].getTipo() == jugador) {
		abajo++;
		if (columna - abajo - 1 < 0 || fila + 1 + abajo > 5) {
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
					&& tablero[i][j].getTipo() != 0) {
				if (i == 0 || i == 6) {
					if (comprobarVertical(tablero, i, j) > 3) {
						return tablero[i][j].getTipo();
					}
				} else if (j == 0 || j == 5) {
					if (comprobarHorizontal(tablero, i, j) > 3) {
						return tablero[i][j].getTipo();
					}
				} else {
					if (comprobarHorizontal(tablero, i, j) > 3
							|| comprobarVertical(tablero, i, j) > 3
							|| comprobarDiagonalDer(tablero, i, j) > 3
							|| comprobarDiagonalIzq(tablero, i, j) > 3) {
						return tablero[i][j].getTipo();
					}
				}
			}

		}
	}
	return 0;
}

char inicioSesion(){
	cout<<"\n1. Registrarse\n"<<endl;
	cout<<"\n2. Iniciar sesión\n"<<endl;
	cout<<"\n9. Salir\n"<<endl;
	cout<<"\n"<<endl;
	cout<<"Opción: "<<endl;

	char linea[2];
	cin>>linea;

	return *linea;
}

char menuInicio() {
	cout<<"\n1. Jugar partida\n"<<endl;
	cout<<"2. Ver estadisticas\n"<<endl;

	cout<<"9. Para salir\n"<<endl;
	cout<<"\n"<<endl;
	cout<<"Opción: "<<endl;

	char linea[2];
	cin>>linea;

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
				cout<<"\nEl numero de columna introducido no es valido. Vuelve a intentarlo."<<endl;
			}

			visualizarTablero(tablero);

			cout<<"Es el turno de Jugador "<<numeroJug<<"\n"<<endl;
			cout<<"En que columna quieres poner tu ficha?\n"<<endl;

			char linea[2];
			cin>>linea;
			columna = *linea - '0';
		} while (columna < 1 || columna > 7);
		if (colocarFicha(tablero, numeroJug, columna - 1)) {
			juegaJug1 = !juegaJug1;
		}
	} while (comprobarVictoria(tablero) == 0);
	visualizarTablero(tablero);
	cout<<"Ha ganado el jugador "<<comprobarVictoria(tablero)<<". Felicidades!\n"<<endl;
//Aqui hay que actualizar las estadisticas de las BDs
}
