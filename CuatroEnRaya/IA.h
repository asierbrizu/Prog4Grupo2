/*
 * Nanami.h
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier
 */

#ifndef IA_H_
#define IA_H_
#include "Mecanicas.h"
int eleccionIA(Ficha **tablero);
int generarNumeroADevolver(int columna, int fila);
Ficha** clonarTablero(Ficha **tablero);
void liberarTablero(Ficha **tablero);
bool comprobrobarVictoriaInminente(Ficha **tablero, int jugador, int objetivo);
int numVictoriaInminente(Ficha **tablero, int jugador, int objetivo);
bool existePeligro(Ficha **tablero, int jugada);
bool derrotaProxima(Ficha **tablero, int jugada);
#endif /* IA_H_ */
