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
	FILE* fEscritura;
	FILE* fLectura;

	fEscritura = fopen("Usuario.txt", "w");
	fLectura = fopen("Datos.txt", "r");

	printf("Asier Brizuela saluda");
	printf("\nAsier Martinez saluda\n");

	Ficha **prueba;
	prueba = (Ficha**) malloc(7 * sizeof(Ficha*));
	int i;
	for (i = 0; i < 7; ++i) {
		prueba[i] = (Ficha*) malloc(6 * sizeof(Ficha));
	}
	limpiar(prueba);
	char sesion;

	do{
		sesion = inicioSesion();
		switch(sesion) {
		case '1':

			printf("\nEscribe tu correo electrónico:\n");
			char usuario[30];
			fgets(usuario, 30, stdin);
			fflush(stdout);

			printf("\nEscribe tu contraseña:\n");
			char contraseya[30];
			fgets(contraseya, 30, stdin);
			fflush(stdout);

			printf("Este es tu usuario %s y esta tu contraseña %s", usuario, contraseya);

			fputs(usuario, fEscritura);

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
			break;

		/*case '2':

			while(){

			}

			break;*/
		default:
			break;
		}
	} while(sesion != '9');

	fclose(fEscritura);
	fclose(fLectura);


}

