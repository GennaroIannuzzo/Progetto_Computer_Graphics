#include "Oggetto.h"

Oggetto::Oggetto() { Oggetto::R = Oggetto::G = Oggetto::B = Oggetto::dim = 0; };

GLfloat Oggetto::getDim(void) { return dim; }

Punto Oggetto::getPosizione(void) { return posizione; }

void Oggetto::setPosizione(Punto punto)
{
	posizione = punto;
}

void Oggetto::Trigger(void) {};