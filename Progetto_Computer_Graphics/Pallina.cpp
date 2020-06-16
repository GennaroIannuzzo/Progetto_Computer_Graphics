#include "Pallina.h"


using namespace std;

Pallina* Pallina::instance = 0;

// Costruttore
Pallina::Pallina()
{
	dim = 2;
	R = 0.0;
	G = 0.0;
	B = 255.0;
	posizione = Punto(0.0, 20.0, 0.0);
	movimento = 0;
	punteggio = 0;
	ballTextures = 0;
	speed = 0.2;
	difficolta = 1;
	angolo = 0;

	sphere = gluNewQuadric();
}

Pallina* Pallina::getInstance()
{
	if (instance == 0)
		instance = new Pallina();

	return instance;
}

/*
	drawObject: disegna la pallina applicando texture e material.
				La rotazione consente di implementare il rotolamento.
*/
void Pallina::drawObject(void)
{
	glTranslatef(posizione.getX(), posizione.gety(), posizione.getZ());

	angolo = (angolo + (int)(speed * 10)) % 360;
	(movimento == 0) ? glRotatef(-angolo, 1, 0, 0) : glRotatef(-angolo, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, ballTextures);

	// MATERIAL SU OGGETTO
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::GrigioScuro);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::GrigioChiaro);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Bianco);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	gluSphere(sphere, 2.0, 32, 16);

}

// ##
void Pallina::setDifficolta(int diff)
{
	speed = 0.1;
	difficolta = diff;
}

// Metodi per il movimento della pallina
void Pallina::moveBall(void)
{
	if (movimento == 0)
		posizione.setZ(posizione.getZ() - speed);
	else
		posizione.setX(posizione.getX() + speed);
}

void Pallina::moveLeft(void) { movimento = 0; }

void Pallina::moveRight(void) { movimento = 1; }

/*
	incrementSpeed: aumenta la velocità della palla entro una soglia limite
*/
void Pallina::incrementSpeed(void) { if(speed < 1.1) speed += 0.1; }

/*
	setTexture: imposta la texture alla pallina
*/
void Pallina::setTexture(string stringa)
{
	string dirname = "Textures/Palla/";

	dirname = dirname + stringa;
	
	ballTextures = SOIL_load_OGL_texture(
		dirname.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

GLUquadric* Pallina::getSphere(void) { return this->sphere; }

void Pallina::resetInstance()
{
	delete instance;
	instance = NULL;
}