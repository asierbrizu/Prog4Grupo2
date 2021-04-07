/*
 * Mecanicas.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aqu� se programa la jugabilidad del programa, la manera en la que se determina si alguien ha ganado la partida y la acci�n de colocar fichas.
 */

#ifndef MECANICAS_H_
#define MECANICAS_H_
#include "Tablero.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int filaLibre(Ficha **tablero, int columna);
bool colocarFicha(Ficha **tablero, int jugador, int columna);
int comprobarVertical(Ficha **tablero, int columna, int fila);
int comprobarHorizontal(Ficha **tablero, int columna, int fila);
int comprobarDiagonalIzq(Ficha **tablero, int columna, int fila);
int comprobarDiagonalDer(Ficha **tablero, int columna, int fila);
int comprobarVictoria(Ficha **tablero);
char menuInicio();
void clearIfNeeded(char *str, int max_line);
void jugarPartida(Ficha **tablero);
#endif /* MECANICAS_H_ */
