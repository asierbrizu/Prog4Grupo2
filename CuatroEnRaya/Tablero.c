/*
 * Tablero.c
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      En este fichero se programara todas las características del tablero..
 */
#include "Tablero.h"
#include "Ficha.h"
#include <stdio.h>
#define SIMBOLO1 'O';
#define SIMBOLO2 'X';

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
	printf("\n---------------\n");
	int j;
	for (j = 5; j >= 0; j--) {
		int i;
		printf("|");
		for (i = 0; i <= 6; i++) {
			printf("%c|", obtenerSimbolo(tablero[i][j].tipo));
		}
		printf("\n");
	}
	printf("---------------\n");
}

void limpiar(Ficha **tablero) {
	int i;
	for (i = 0; i < 7; i++) {
		int j;
		for (j = 0; j < 6; ++j) {
			tablero[i][j].tipo = 0;
		}
	}
}
