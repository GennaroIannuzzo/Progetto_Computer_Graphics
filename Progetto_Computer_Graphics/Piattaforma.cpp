#include "Piattaforma.h"

using namespace std;

void Piattaforma::calcolaPosizione(GLfloat& x, GLfloat& y, GLfloat& z)
{
	GLfloat dimensione_oggetto = oggetto->getDim() / 2;
	
	GLfloat dim_mezzi = dim / 2;
	GLfloat posizione_x_min = -dim_mezzi + dimensione_oggetto;
	GLfloat posizione_x_max = dim_mezzi - dimensione_oggetto;

	GLfloat posizione_z_max = dim_mezzi - dimensione_oggetto;
	GLfloat posizione_z_min = -dim_mezzi + dimensione_oggetto;

	y = 20.0;
	x = posizione_x_min + rand() % int((posizione_x_max - posizione_x_min));
	z = posizione_z_min + rand() % int((posizione_z_max - posizione_z_min));
}

// Costruttori
Piattaforma::Piattaforma()
{
	// this->R = 255.0;
	// this->G = 0.0;
	// this->B = 0.0;
	
	//this->R = 62.0  / 255.0;
	//this->G = 110.0 / 255.0;
	//this->B = 163.0 / 255.0;
	
	this->R = 109.0  / 255.0;
	this->G = 187.0 / 255.0;
	this->B = 254.0 / 255.0;
	this->dim = 30;
	
	/*
		creazione randomica di un oggetto sulla piattaforma
		0 -> monete
		1 -> ostacolo
		> 1 -> nulla
	*/

	tipo = rand() % 3;
	
	GLfloat x, y, z;
	
	switch (tipo)
	{
	case 0:
		oggetto = new Monete();
		calcolaPosizione(x, y, z);
		oggetto->setPosizione(Punto(x, y, z));
		break;
	case 1:
		oggetto = new Ostacolo();
		calcolaPosizione(x, y, z);
		oggetto->setPosizione(Punto(x, y, z));
		break;

	default:
		oggetto = NULL;
		break;
	}

}

Piattaforma::Piattaforma(Punto valPunto) : Piattaforma()
{ 
	posizione = valPunto; 
}

// Metodi
void Piattaforma::drawObject(void)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::AzzurroTenue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Colors::Azzurro);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Bianco);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	
	glTranslatef(posizione.getX(), posizione.gety(), posizione.getZ());
	glutSolidCube(dim);
	
	if (tipo < 2)
	{
		glPushMatrix();
			glTranslatef(oggetto->getPosizione().getX(), oggetto->getPosizione().gety(), oggetto->getPosizione().getZ());
			oggetto->drawObject();
		glPopMatrix();
		
	}
}

void Piattaforma::dropOggetto(void) { tipo = 2; }

Oggetto* Piattaforma::getOggetto(void) { return oggetto; }
int Piattaforma::getTipo(void) { return tipo; }

// Distruttore
Piattaforma::~Piattaforma() {}