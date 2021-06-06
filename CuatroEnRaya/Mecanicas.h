/*
 * Mecanicas.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aquí se programa la jugabilidad del programa, la manera en la que se determina si alguien ha ganado la partida y la acción de colocar fichas.
 */

#ifndef MECANICAS_H_
#define MECANICAS_H_
#include "Tablero.h"
#include "Jugador.h"
#include "sqlite3.h"
#include <iostream>
using namespace std;
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int OBJETIVO = 4; //Estandar: 4
int filaLibre(Ficha **tablero, int columna);
bool colocarFicha(Ficha **tablero, int jugador, int columna);
int comprobarVertical(Ficha **tablero, int columna, int fila);
int comprobarHorizontal(Ficha **tablero, int columna, int fila);
int comprobarDiagonalIzq(Ficha **tablero, int columna, int fila);
int comprobarDiagonalDer(Ficha **tablero, int columna, int fila);
int comprobarVictoria(Ficha **tablero, int objetivo);
int numeroDeVictorias(Ficha **tablero, int objetivo);
char menuInicio();
void iniciarSesion(sqlite3 *db, Jugador *j);
char inicioSesion();
void clearIfNeeded(char *str, int max_line);
void jugarPartida(Ficha **tablero, bool IA, Jugador jugador, Jugador jugador2,
		sqlite3 *db);
bool empate(Ficha **tablero);
#endif /* MECANICAS_H_ */
