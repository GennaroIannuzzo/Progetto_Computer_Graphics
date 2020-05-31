#include "Piattaforma.h"

using namespace std;

// Attributi Statici
GLfloat Piattaforma::dim = 30;
GLfloat Piattaforma::R = 255.0;
GLfloat Piattaforma::G = 0.0;
GLfloat Piattaforma::B = 0.0;

// Costruttori
Piattaforma::Piattaforma(){}
Piattaforma::Piattaforma(Punto valPunto) { punto = valPunto; }

// Getter
Punto Piattaforma::getPunto() { return punto; }
GLfloat Piattaforma::getDim() { return dim; }

// Metodi
void Piattaforma::drawPiattaforma(void)
{
	// glColor3f(R, G, B);
	glTranslatef(punto.getX(), punto.getY(), punto.getZ());
	glutSolidCube(dim);
}

// Distruttore
Piattaforma::~Piattaforma() {}