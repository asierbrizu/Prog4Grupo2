/*
 * Main.c
 *
 *  Created on: 4 abr. 2021
 *      Author: Asier
 */

#include "Mecanicas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	printf("Asier Brizuela saluda");
	printf("Asier Martinez saluda");

	Ficha **prueba;
	prueba = (Ficha**) malloc(7 * sizeof(Ficha*));
	int i;
	for (i = 0; i < 7; ++i) {
		prueba[i] = (Ficha*) malloc(6 * sizeof(Ficha));
	}
	limpiar(prueba);

	char opcion;
	do {
		opcion = menuInicio();
		switch (opcion) {
		case '1':
			jugarPartida(prueba);
			break;
		default:
			break;
		}
	} while (opcion != '9');

	//Liberar tablero
	for (i = 0; i < 7; i++) {
		free(prueba[i]);
	}
	free(prueba);

}

