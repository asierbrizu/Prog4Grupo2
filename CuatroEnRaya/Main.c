/*
 * Main.c
 *
 *  Created on: 4 abr. 2021
 *      Author: Asier
 */

#include "Mecanicas.h"
#include <stdio.h>
#include <stdlib.h>

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

	colocarFicha(prueba, 1, 0);

	colocarFicha(prueba, 1, 1);
	colocarFicha(prueba, 2, 2);
	colocarFicha(prueba, 1, 3);
	colocarFicha(prueba, 2, 3);

	visualizarTablero(prueba);

	printf("Ha ganado %i", comprobarVictoria(prueba));
	limpiar(prueba);
	visualizarTablero(prueba);

	//Liberar tablero
	for (i = 0; i < 7; i++) {
		free(prueba[i]);
	}
	free(prueba);

}

