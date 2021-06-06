/*
 * Tablero.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      En este fichero se programara todas las características del tablero..
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "Ficha.h"
const int COLUMNAS = 7; //Estandar: 7
const int FILAS = 6; //Estandar: 6
#define SIMBOLO1 'O';
#define SIMBOLO2 'X';

char obtenerSimbolo(int num);
void visualizarTablero(Ficha **tablero);
void limpiar(Ficha **tablero);
#endif /* TABLERO_H_ */
