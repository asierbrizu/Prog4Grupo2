/*
 * Jugador.cpp
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier
 */
#include "Jugador.h"
Jugador::Jugador(){
	this->email="";
	this->contraseya="";
}
Jugador::Jugador(char *email,char *contrasenya){
this->email=email;
this->contraseya=contrasenya;
}
Jugador::~Jugador(){

}

	char* Jugador::getEMail(){
return email;
	}
	char* Jugador::getContrasenya(){
return contraseya;
	}

	void Jugador::setEMail(char *mail){
		this->email=mail;
	}
	void Jugador::setContrasenya(char *contra){
this->contraseya=contra;
	}


