/*
 * Tablero.c
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      En este fichero se programara todas las características del tablero..
 */
#include "Tablero.h"
#include <iostream>
using namespace std;

char obtenerSimbolo(int num) {
	switch (num) {
	case 1:
		return SIMBOLO1;
		break;
	case 2:
		return SIMBOLO2;
		break;
	default:
		return ' ';
		break;
	}
}

void visualizarTablero(Ficha **tablero) {
	for (int n = 0; n < COLUMNAS * 2 + 1; n++) {
		cout << "-";
	}
	cout << endl;
	for (int n = 0; n < COLUMNAS; n++) {
		cout << " " << n + 1;
	}
	cout << endl;
	int j;
	for (j = FILAS - 1; j >= 0; j--) {
		int i;
		cout << "|";
		for (i = 0; i <= COLUMNAS - 1; i++) {
			cout << obtenerSimbolo(tablero[i][j].getTipo()) << "|";
		}
		cout << endl;
	}
	for (int n = 0; n < COLUMNAS * 2 + 1; n++) {
		cout << "-";
	}
	cout << endl;
}

void limpiar(Ficha **tablero) {
	int i;
	for (i = 0; i < COLUMNAS; i++) {
		int j;
		for (j = 0; j < FILAS; ++j) {
			tablero[i][j].setTipo(0);
		}
	}
}
