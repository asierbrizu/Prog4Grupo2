/*
 * Jugador.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aqu� se encontrar� la programaci�n relacionada con el inicio de sesi�n de jugadores, y visualizaci�n de estad�sticas.
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_

class Jugador {
private:
	char *email;
	char *contraseya;
public:
	Jugador();
	Jugador(char *email, char *contrasenya);
	~Jugador();

	char* getEMail();
	char* getContrasenya();

	void setEMail(char *mail);
	void setContrasenya(char *contra);
};

#endif /* JUGADOR_H_ */
