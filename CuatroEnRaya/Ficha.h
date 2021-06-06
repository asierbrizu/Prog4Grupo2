/*
 * Ficha.h
 *
 *  Created on: 30 mar. 2021
 *      Author: Asier
 *      En este fichero se programara todas las características de las fichas.
 */

#ifndef FICHA_H_
#define FICHA_H_

class Ficha {
private:
	int tipo;
public:
	Ficha();
	Ficha(int tipo);
	~Ficha();

	int getTipo();
	void setTipo(int tipo);
};

#endif /* FICHA_H_ */
