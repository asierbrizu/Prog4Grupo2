/*
 * BD.h
 *
 *  Created on: 4 jun. 2021
 *      Author: Asier
 */

#ifndef BD_H_
#define BD_H_

#include "sqlite3.h"
#include "Jugador.h"



		int crearUsuario(sqlite3 *db,Jugador j);
		int confirmarUsuario(sqlite3 *db, Jugador j);
		int mostrarEstadisticas(sqlite3 *db, Jugador j);
		int sumarVictoria(sqlite3 *db, Jugador j);
		int sumarPartida(sqlite3 *db, Jugador j);



#endif /* BD_H_ */
