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
int generarNumeroADevolver(int columna,int fila);
Ficha ** clonarTablero(Ficha **tablero);
void liberarTablero(Ficha **tablero);
bool comprobrobarVictoriaInminente(Ficha **tablero,int jugador,int objetivo);
int numVictoriaInminente(Ficha **tablero,int jugador,int objetivo);
#endif /* IA_H_ */
