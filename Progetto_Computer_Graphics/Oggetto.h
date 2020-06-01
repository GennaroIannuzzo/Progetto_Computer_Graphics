#pragma once
#include "Punto.h"
#include <iostream>

class Oggetto
{
protected:

	GLfloat R;
	GLfloat G;
	GLfloat B;
	GLfloat dim;
	Punto posizione;

public:
	Oggetto();
	
	// metodi getter 
	GLfloat getR(void);
	GLfloat getG(void);
	GLfloat getB(void);
	GLfloat getDim(void);

	Punto getPosizione(void);

	// metodo di drawing virtual 
	virtual void drawObject(void) = 0;
};

