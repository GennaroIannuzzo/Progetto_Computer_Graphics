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

	GLfloat getDim(void);

	Punto getPosizione(void);

	// metodo setter
	void setPosizione(Punto punto);

	// metodo di drawing virtual 
	virtual void drawObject(void) = 0;
	
	virtual void Trigger(void);
};

