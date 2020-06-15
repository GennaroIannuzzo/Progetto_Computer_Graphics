/*
	Oggetto: La classe oggetto è una primitiva generica che definisce la struttura e i metodi di base utili alle classi figlie.
			 I metodi che dovranno essere implementati dalle classi figlie sono drawObject per disegnare l'oggetto custom 
			 e Trigger per effettuare i controlli del bounding box.
*/
#pragma once
#include <iostream>
#include "Punto.h"
#include "SoundManager.h"

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

