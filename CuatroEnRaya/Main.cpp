/*
 * Main.c
 *
 *  Created on: 4 abr. 2021
 *      Author: Asier Brizuela
 */

#include "Mecanicas.h"
#include "Jugador.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {


	Jugador jugador;

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


			cout <<"\nEscribe tu correo electrónico:\n"<<endl;
			char usuario[30];
			cin>>usuario;



			cout<<"\nEscribe tu contraseña:\n"<<endl;
			char contraseya[30];
			cin>>contraseya;



			cout<<"\nRepite tu contraseña:\n"<<endl;
			char contraseya2[30];
			cin>>contraseya2;

			while (strcmp(contraseya, contraseya2) != 0) {


							cout<<"\nEscribe tu contraseña:\n"<<endl;
							char contraseya[30];
							cin>>contraseya;



							cout<<"\nRepite tu contraseña:\n"<<endl;
							char contraseya2[30];
							cin>>contraseya2;

			}


			cout<<"Este es tu usuario "<<usuario<<" y esta es tu contraseña "<<contraseya<<".";

			jugador.setEMail(usuario);
			jugador.setContrasenya(contraseya);

			//Aqui hay que crear el usuario en la Base de Datos



			char opcion;
			do {
				opcion = menuInicio();
				switch (opcion) {
				case '1':

					cout<<"Contra quien quieres jugar?"<<endl;
					cout<<"1. Contra otro jugador."<<endl;
					cout<<"2. Contra la IA."<<endl;
					char opcionOponente;
					cin>>opcionOponente;

					switch(opcionOponente){
					case '1':
						jugarPartida(tablero);
						break;
					}





					break;
				case '2':

					cout<<"\nAhora se mostraran las estadisticas:\n"<<endl;



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
			//Aqui hay que iniciar sesión (y crear una)
			break;
		default:
			break;
		}
	} while (sesion != '9');

}

