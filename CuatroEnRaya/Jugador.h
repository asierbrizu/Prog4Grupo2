/*
 * Jugador.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      Aquí se encontrará la programación relacionada con el inicio de sesión de jugadores, y visualización de estadísticas.
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
