#pragma once
#include "Punto.h"
#include <iostream>
#include <cstdlib>

class Piattaforma {
private:

	// Attributi
	Punto punto;

	static GLfloat dim;
	static GLfloat R;
	static GLfloat G;
	static GLfloat B;

public:

	// Costruttori
	Piattaforma();
	Piattaforma(Punto valPunto);

	// Getter
	Punto getPunto();
	static GLfloat getDim();

	// Metodi
	void drawPiattaforma(void);

	// Distruttore
	~Piattaforma();
};