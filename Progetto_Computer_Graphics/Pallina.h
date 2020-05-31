#include "Punto.h"
#include <iostream>

#pragma once
class Pallina
{
private:
	
	// Attributi
	Punto posizione;
	GLfloat speed;
	int movimento;
	int difficolta;
	static GLfloat dim;
	static GLfloat R;
	static GLfloat G;
	static GLfloat B;

public:

	// Costruttori
	Pallina(int difficolta);

	// Getter
	Punto getPosizione(void);

	// Metodi
	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	void drawPallina(void);
	void moveBall(void);
};