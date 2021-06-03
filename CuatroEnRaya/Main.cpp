/*
 * Main.c
 *
 *  Created on: 4 abr. 2021
 *      Author: Asier
 */

extern "C" {
#include "Mecanicas.h"
#include "Jugador.h"
#include "Tablero.h"
};
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	//FILE *fEscritura;
	//FILE *fLectura;

	Jugador jugador;

	//fEscritura = fopen("Usuario.txt", "a");
	//fLectura = fopen("Datos.txt", "r");

	Ficha **tablero;
	tablero = (Ficha**) malloc(7 * sizeof(Ficha*));
	int i;
	for (i = 0; i < 7; ++i) {
		tablero[i] = (Ficha*) malloc(6 * sizeof(Ficha));
	}
	limpiar(tablero);
	char sesion;

	do {
		sesion = inicioSesion();
		switch (sesion) {
		case '1':

			//printf("\nEscribe tu correo electrónico:\n");
			cout <<"\nEscribe tu correo electrónico:\n"<<endl;
			char usuario[30];
			cin>>usuario;
			//fflush(stdout);
			//fgets(usuario, 30, stdin);

			//printf("\nEscribe tu contraseña:\n");
			cout<<"\nEscribe tu contraseña:\n"<<endl;
			char contraseya[30];
			cin>>contraseya;
			//fflush(stdout);
			//fgets(contraseya, 30, stdin);

			//printf("\nRepite tu contraseña:\n");
			cout<<"\nRepite tu contraseña:\n"<<endl;
			char contraseya2[30];
			cin>>contraseya2;
			//fflush(stdout);
			//fgets(contraseya2, 30, stdin);

			while (strcmp(contraseya, contraseya2) != 0) {

				//printf("\nEscribe tu contraseña:\n");
							cout<<"\nEscribe tu contraseña:\n"<<endl;
							char contraseya[30];
							cin>>contraseya;
							//fflush(stdout);
							//fgets(contraseya, 30, stdin);

							//printf("\nRepite tu contraseña:\n");
							cout<<"\nRepite tu contraseña:\n"<<endl;
							char contraseya2[30];
							cin>>contraseya2;
							//fflush(stdout);
							//fgets(contraseya2, 30, stdin);
			}

			//printf("Este es tu usuario %s y esta tu contraseña %s", usuario,
			//contraseya);
			cout<<"Este es tu usuario "<<usuario<<" y esta es tu contraseña "<<contraseya<<".";
			strcpy(jugador.usuario, usuario);
			strcpy(jugador.contraseya, contraseya);

			//Aqui hay que crear el usuario en la Base de Datos

			//fputs(usuario, fEscritura);
			//fputs(contraseya, fEscritura);

			char opcion;
			do {
				opcion = menuInicio();
				switch (opcion) {
				case '1':
					jugarPartida(tablero);
					break;
				case '2':

					cout<<"\nAhora se mostraran las estadisticas:\n"<<endl;

					//if (fLectura == NULL) {
					//	printf("nError opening file.nExiting program.n");
					//}

					/*char estadistic[60];
					while (fgets(estadistic, 100, fLectura) != NULL) {
						printf("%s", estadistic);
					}
*/
					break;
				default:
					break;
				}
			} while (opcion != '9');

			//Liberar tablero
			for (i = 0; i < 7; i++) {
				free(tablero[i]);
			}
			free(tablero);
			break;
		case '2':
			cout<<"Prueba inicio sesión"<<endl;
			break;
		default:
			break;
		}
	} while (sesion != '9');

	//fclose(fEscritura);
	//fclose(fLectura);

}

