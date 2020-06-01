#include "Piattaforma.h"

using namespace std;

// Costruttori
Piattaforma::Piattaforma()
{
	this->R = 255.0;
	this->G = 0.0;
	this->B = 0.0;
	this->dim = 30;
}
Piattaforma::Piattaforma(Punto valPunto) : Piattaforma()
{ 
	posizione = valPunto; 
}

// Metodi
void Piattaforma::drawObject(void)
{
	// glColor3f(R, G, B);
	glTranslatef(posizione.getX(), posizione.getY(), posizione.getZ());
	glutSolidCube(dim);
}

// Distruttore
Piattaforma::~Piattaforma() {}