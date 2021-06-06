/*
 * Main.c
 *
 *  Created on: 4 abr. 2021
 *      Author: Asier Brizuela
 */

#include "BD.h"
#include "sqlite3.h"
#include "Mecanicas.h"
#include "Jugador.h"
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Jugador IA;
	Jugador jugador2;

	IA.setEMail("IA");
	IA.setContrasenya("Invencible");

	int result;

	sqlite3 *db;

	result = sqlite3_open("BD.sqlite", &db);
	if(result != SQLITE_OK){
		printf("Error opening database\n");
		return result;
	}

			printf("Database opened\n");

	Jugador jugador;

	Ficha **tablero = new Ficha*[COLUMNAS];
	int i;
	for (i = 0; i < COLUMNAS; ++i) {
		tablero[i] = new Ficha[FILAS];
	}
	limpiar(tablero);
	char sesion;

	do {
		sesion = inicioSesion();
		switch (sesion) {
		case '1':

			cout << "\nEscribe tu correo electrónico:\n" << endl;
			char usuario[30];
			cin >> usuario;

			cout << "\nEscribe tu contraseña:\n" << endl;
			char contraseya[30];
			cin >> contraseya;

			cout << "\nRepite tu contraseña:\n" << endl;
			char contraseya2[30];
			cin >> contraseya2;

			while (strcmp(contraseya, contraseya2) != 0) {

				cout << "\nEscribe tu contraseña:\n" << endl;
				char contraseya[30];
				cin >> contraseya;

				cout << "\nRepite tu contraseña:\n" << endl;
				char contraseya2[30];
				cin >> contraseya2;

			}

			cout << "Este es tu usuario " << usuario
					<< " y esta es tu contraseña " << contraseya << ".";

			jugador.setEMail(usuario);
			jugador.setContrasenya(contraseya);

			//Aqui hay que crear el usuario en la Base de Datos

			result = crearUsuario(db, jugador);

			cout<< "Usuario guardado" <<endl;

			if (result != SQLITE_OK) {
				printf("Error creating Usuario\n");
				printf("%s\n", sqlite3_errmsg(db));
				return result;
			}

			char opcion;
			do {
				opcion = menuInicio();
				switch (opcion) {
				case '1':

					cout << "Contra quien quieres jugar?" << endl;
					cout << "1. Contra otro jugador." << endl;
					cout << "2. Contra la IA." << endl;
					char opcionOponente;
					cin >> opcionOponente;

					switch (opcionOponente) {
					case '1':
						//Se pide que el jugador 2 inicie sesión

						cout << "\nEscribe tu correo electrónico:\n" << endl;
						char inicioUsuario2[30];
						cin >> inicioUsuario2;

						cout << "\nEscribe tu contraseña:\n" << endl;
						char inicioContraseya2[30];
						cin >> inicioContraseya2;

						jugador2.setEMail(inicioUsuario2);
						jugador2.setContrasenya(inicioContraseya2);

						result = confirmarUsuario(db, jugador2);

						if (result != SQLITE_OK) {
							printf("This isn't your account\n");
							printf("%s\n", sqlite3_errmsg(db));
							return result;
						}

						cout << "Sesion iniciada" << endl;

						sumarPartida(db, jugador);
						sumarPartida(db, jugador2);

						jugarPartida(tablero, false, jugador, jugador2, db); //Pendiente cambiar parametros para recibir dos usuarios
						break;

					case '2':
						sumarPartida(db, jugador);
						sumarPartida(db, IA);

						jugarPartida(tablero, true, jugador, IA, db); //Pendiente cambiar parametros para recibir dos usuarios (el segundo la IA)
						break;
					}

					break;
				case '2':

					cout << "\nAhora se mostraran las estadisticas:\n" << endl;

					result = mostrarEstadisticas(db, jugador);
					if (result != SQLITE_OK) {
						printf("Error with stadistic\n");
						printf("%s\n", sqlite3_errmsg(db));
						return result;
					}

					break;
				default:
					break;
				}
			} while (opcion != '9');

			//Liberar tablero
			for (i = 0; i < COLUMNAS; i++) {
				delete[] tablero[i];
			}
			delete[] tablero;

			break;
		case '2':
			//Aqui hay que iniciar sesión (y crear una)

			cout << "\nEscribe tu correo electrónico:\n" << endl;
			char inicioUsuario[30];
			cin >> inicioUsuario;

			cout << "\nEscribe tu contraseña:\n" << endl;
			char inicioContraseya[30];
			cin >> inicioContraseya;

			jugador.setEMail(inicioUsuario);
			jugador.setContrasenya(inicioContraseya);

			result = confirmarUsuario(db, jugador);

			if (result != SQLITE_OK) {
				printf("This isn't your account\n");
				printf("%s\n", sqlite3_errmsg(db));
				return result;
			}

			cout << "Sesion iniciada" << endl;

			do {
				opcion = menuInicio();
				switch (opcion) {
				case '1':

					cout << "Contra quien quieres jugar?" << endl;
					cout << "1. Contra otro jugador." << endl;
					cout << "2. Contra la IA." << endl;
					char opcionOponente;
					cin >> opcionOponente;

					switch (opcionOponente) {
					case '1':
						//Se pide que el jugador 2 inicie sesión


						sumarPartida(db, jugador);
						sumarPartida(db, jugador2);

						jugarPartida(tablero, false, jugador, jugador2, db); //Pendiente cambiar parametros para recibir dos usuarios
						break;

					case '2':
						sumarPartida(db, jugador);
						sumarPartida(db, IA);

						jugarPartida(tablero, true, jugador, IA, db); //Pendiente cambiar parametros para recibir dos usuarios (el segundo la IA)
						break;
					}

					break;
				case '2':

					cout << "\nAhora se mostraran las estadisticas:\n" << endl;

					result = mostrarEstadisticas(db, jugador);
					if (result != SQLITE_OK) {
						printf("Error with stadistic\n");
						printf("%s\n", sqlite3_errmsg(db));
						return result;
					}

					break;
				default:
					break;
				}
			} while (opcion != '9');

			//Liberar tablero
			for (i = 0; i < COLUMNAS; i++) {
				delete[] tablero[i];
			}
			delete[] tablero;

			break;
		default:
			result = sqlite3_close(db);
			if (result != SQLITE_OK){
				printf("Error closing database\n");
				return result;
			}
			printf("Database closed\n");
			break;
		}
	} while (sesion != '9');

}

