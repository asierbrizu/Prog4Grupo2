/*
 * Ficha.cpp
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier Brizuela
 */

#include "Ficha.h"
Ficha::Ficha() {
	this->tipo = 0;
}
Ficha::Ficha(int tipo) {
	this->tipo = tipo;
}
Ficha::~Ficha() {
}
int Ficha::getTipo() {
	return tipo;
}

void Ficha::setTipo(int tipo) {
	this->tipo = tipo;
}

