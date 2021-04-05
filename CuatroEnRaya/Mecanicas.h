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
#include <stdbool.h>
int filaLibre(Ficha **tablero, int columna);
bool colocarFicha(Ficha **tablero, int jugador, int columna);
int comprobarVertical(Ficha **tablero, int columna, int fila);
int comprobarHorizontal(Ficha **tablero, int columna, int fila);
int comprobarDiagonalIzq(Ficha **tablero, int columna, int fila);
int comprobarDiagonalDer(Ficha **tablero, int columna, int fila);
int comprobarVictoria(Ficha **tablero);
#endif /* MECANICAS_H_ */
