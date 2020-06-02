#include "Oggetto.h"

Oggetto::Oggetto() {};

GLfloat Oggetto::getR(void) { return R; }
GLfloat Oggetto::getG(void) { return G; }
GLfloat Oggetto::getB(void) { return B; }
GLfloat Oggetto::getDim(void) { return dim; }

Punto Oggetto::getPosizione(void) { return posizione; }

void Oggetto::setPosizione(Punto punto)
{
	posizione = punto;
}

void Oggetto::Trigger(void) {};