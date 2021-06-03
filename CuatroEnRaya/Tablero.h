/*
 * Tablero.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      En este fichero se programara todas las caracter�sticas del tablero..
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "Ficha.h"

char obtenerSimbolo(int num);
void visualizarTablero(Ficha **tablero);
void limpiar(Ficha **tablero);
#endif /* TABLERO_H_ */
