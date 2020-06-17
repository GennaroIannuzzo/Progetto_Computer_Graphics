#include "Piattaforma.h"

using namespace std;

/* Calcola la posizione randomica dell'oggetto da porre sulla piattaforma */
void Piattaforma::calcolaPosizione(GLfloat& x, GLfloat& y, GLfloat& z)
{
	// Recupera la metà della dimensione dell'oggetto
	GLfloat dimensione_oggetto = oggetto->getDim() / 2;
	
	// Recupera la metà della dimensione della piattaforma
	GLfloat dim_mezzi = dim / 2;

	// Calcola i bordi entro cui può rientrare l'oggetto
	GLfloat posizione_x_min = -dim_mezzi + dimensione_oggetto;
	GLfloat posizione_x_max = dim_mezzi - dimensione_oggetto;
	GLfloat posizione_z_max = dim_mezzi - dimensione_oggetto;
	GLfloat posizione_z_min = -dim_mezzi + dimensione_oggetto;

	// Determina la posizione dell'oggetto
	y = 20.0;
	x = posizione_x_min + rand() % int((posizione_x_max - posizione_x_min));
	z = posizione_z_min + rand() % int((posizione_z_max - posizione_z_min));
}

// Costruttori
Piattaforma::Piattaforma()
{
	this->dim = 30;
	
	tipo = rand() % 3;
	
	GLfloat x, y, z;
	
	switch (tipo)
	{
	// Crea una moneta
	case 0:
		oggetto = new Monete();
		calcolaPosizione(x, y, z);
		oggetto->setPosizione(Punto(x, y, z));
		break;
	// Crea un ostacolo
	case 1:
		oggetto = new Ostacolo();
		calcolaPosizione(x, y, z);
		y -= 3;
		oggetto->setPosizione(Punto(x, y, z));
		break;
	// Non crea nessun oggetto
	default:
		oggetto = NULL;
		break;
	}

}

// Costruttore con aggiunta di posizione
Piattaforma::Piattaforma(Punto valPunto) : Piattaforma() { posizione = valPunto; }

// Metodi
/* Disegna la piattaforma */
void Piattaforma::drawObject(void)
{
	// Imposta le caratteristiche del material
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::AzzurroTenue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Colors::Azzurro);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Bianco);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	
	// Sposta la piattaforma nella sua posizione
	glTranslatef(posizione.getX(), posizione.gety(), posizione.getZ());
	
	// Disegna il cubo
	glutSolidCube(dim);
	
	// Posizione l'oggetto sulla piattaforma
	if (tipo < 2)
	{
		glPushMatrix();
			glTranslatef(oggetto->getPosizione().getX(), oggetto->getPosizione().gety(), oggetto->getPosizione().getZ());
			oggetto->drawObject();
		glPopMatrix();
	}
}

/* Elimina l'oggetto dalla piattaforma */
void Piattaforma::dropOggetto(void) { tipo = 2; }

/* Restituisci oggetto */
Oggetto* Piattaforma::getOggetto(void) { return oggetto; }

/* Restituisci tipo di oggetto */
int Piattaforma::getTipo(void) { return tipo; }

// Distruttore
Piattaforma::~Piattaforma() {}