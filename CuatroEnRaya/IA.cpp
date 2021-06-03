/*
 * Nanami.cpp
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier Brizuela
 */

#include "IA.h"

Ficha ** clonarTablero(Ficha **tablero){
	Ficha **copia=new Ficha*[COLUMNAS];
		int i;
		for (i = 0; i < COLUMNAS; ++i) {
			copia[i]=new Ficha[FILAS];
		}

		for (int i = 0; i < COLUMNAS; ++i) {
			for (int j = 0; j < FILAS; ++j) {
copia[i][j].setTipo(tablero[i][j].getTipo());
			}
		}
		return copia;
}





int eleccionIA(Ficha **tablero){

	//1. Comprueba victoria inminente para IA.
if (comprobrobarVictoriaInminente(tablero, 2,OBJETIVO)) {
	cout<<"Colocando en primer caso"<<endl;
	return numVictoriaInminente(tablero, 2,OBJETIVO);
}

//2. Impide victoria inminente para Jugador.
if (comprobrobarVictoriaInminente(tablero, 1,OBJETIVO)) {
	cout<<"Colocando en segundo caso"<<endl;
	return numVictoriaInminente(tablero, 1,OBJETIVO);
}

//3. Comprueba victorias próximas para IA.
for(int n=0;n<COLUMNAS;n++){
bool seRealiza=false;
int jugada=-1;
Ficha **posibilidad=clonarTablero(tablero);
colocarFicha(posibilidad, 2, n);
if (!comprobrobarVictoriaInminente(posibilidad, 1,OBJETIVO)) {
	if (comprobrobarVictoriaInminente(posibilidad, 2,OBJETIVO)) {
		colocarFicha(posibilidad, 1,numVictoriaInminente(posibilidad, 2,OBJETIVO));
		if (comprobrobarVictoriaInminente(posibilidad, 2,OBJETIVO)) {
			seRealiza=true;
			jugada= numVictoriaInminente(posibilidad, 2,OBJETIVO);
		}
	}
}

liberarTablero(posibilidad);
if (seRealiza) {
	cout<<"Colocando en tercer caso"<<endl;
	return jugada;
}
}

//4 Intentar alinear 3

for(int n=0;n<COLUMNAS;n++){
	Ficha **posibilidad=clonarTablero(tablero);
	bool seRealiza=false;
	int jugada=-1;
	colocarFicha(posibilidad, 2, n);
	if (numeroDeVictorias(posibilidad, OBJETIVO-1)>numeroDeVictorias(tablero, OBJETIVO-1)) {
seRealiza=true;
jugada=n;
	}
	liberarTablero(posibilidad);
	if (seRealiza) {
		cout<<"Colocando en cuarto caso"<<endl;
		return jugada;
	}
}


//5 Evitar alinear 3
for(int n=0;n<COLUMNAS;n++){
	Ficha **posibilidad=clonarTablero(tablero);
	bool seRealiza=false;
	int jugada=-1;
	colocarFicha(posibilidad, 1, n);
	if (numeroDeVictorias(posibilidad, OBJETIVO-1)>numeroDeVictorias(tablero, OBJETIVO-1)) {
seRealiza=true;
jugada=n;
	}
	liberarTablero(posibilidad);
	if (seRealiza) {
		cout<<"Colocando en quinto caso"<<endl;
		return jugada;
	}
}

//6. Evita victorias próximas para Jugador.
for(int n=0;n<COLUMNAS;n++){
bool seRealiza=true;
int jugada=n;
Ficha **posibilidad=clonarTablero(tablero);
colocarFicha(posibilidad, 2, n);
if (!comprobrobarVictoriaInminente(posibilidad, 1,OBJETIVO)) {
	for(int m=0;m<COLUMNAS;m++){
	Ficha **posibilidad2=clonarTablero(posibilidad);
	if (comprobrobarVictoriaInminente(posibilidad2, 1,OBJETIVO)) {
		colocarFicha(posibilidad2, 2, numVictoriaInminente(posibilidad2, 1,OBJETIVO));
		if (comprobrobarVictoriaInminente(posibilidad2, 1,OBJETIVO)) {
			seRealiza=false;
		}
	}
	liberarTablero(posibilidad2);
	if (seRealiza) {
		break;
	}
	}
}else {
	seRealiza=false;
}

liberarTablero(posibilidad);
if (seRealiza&&filaLibre(tablero, jugada)<FILAS) {
	cout<<"Colocando en sexto caso"<<endl;
	return jugada;
}
}

for (int libre = 0; libre < COLUMNAS; libre++) {
	if (filaLibre(tablero, libre)<FILAS) {
		cout<<"Colocando en quinto caso"<<endl;
		return libre;
	}
}

cout<<"Colocando en error caso"<<endl;
	return -1;
}
bool comprobrobarVictoriaInminente(Ficha **tablero,int jugador,int objetivo){
	bool seRealiza=false;
	for(int n=0;n<COLUMNAS;n++){

	Ficha **posibilidad=clonarTablero(tablero);
	colocarFicha(posibilidad, jugador, n);
	if (comprobarVictoria(posibilidad,objetivo)==jugador) {
		seRealiza=true;

	}
	liberarTablero(posibilidad);

	}
	return seRealiza;
}

int numVictoriaInminente(Ficha **tablero,int jugador,int objetivo){
	for(int n=0;n<COLUMNAS;n++){
	bool seRealiza=false;
	int jugada=-1;
	Ficha **posibilidad=clonarTablero(tablero);
	colocarFicha(posibilidad, jugador, n);
	if (comprobarVictoria(posibilidad,objetivo)==jugador) {
		seRealiza=true;
		jugada=n;
	}
	liberarTablero(posibilidad);
	if (seRealiza) {
		return jugada;
	}
	}
	return 0;
}

void liberarTablero(Ficha **tablero){
	for (int i = 0; i < COLUMNAS; i++) {
					delete[] tablero[i];
				}
				delete[] tablero;
}

