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
	
	indiceTexture = 0;

	speed = 0.1;
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

void Pallina::setDifficolta(int diff)
{
	speed = 0.1;
	difficolta = diff;
}

// Metodi
void Pallina::moveBall(void)
{
	if (movimento == 0)
		posizione.setZ(posizione.getZ() - speed);
	else
		posizione.setX(posizione.getX() + speed);
}

void Pallina::moveLeft(void) { movimento = 0; }

void Pallina::moveRight(void) { movimento = 1; }

void Pallina::incrementSpeed(void) { if(speed < 0.4) speed += 0.1; }

void Pallina::setTexture(int textureAttiva)
{
	indiceTexture = textureAttiva;
	cout << "la texture scelta e' " << textureAttiva << endl;
}

void Pallina::drawObject(void) 
{
	// glColor3f(R, G, B);
	glTranslatef(posizione.getX(), posizione.gety(), posizione.getZ());

	angolo = (angolo + 1) % 360;
	(movimento == 0) ? glRotatef(-angolo, 1, 0, 0) : glRotatef(-angolo, 0, 0, 1);
	
	// glutSolidSphere(dim, (int)dim*6, (int)dim*6);
	// glutSolidCube(dim);
	glBindTexture(GL_TEXTURE_2D, ballTextures[indiceTexture]);

	// MATERIAL SU OGGETTO
	glMaterialfv(GL_FRONT, GL_AMBIENT,  Colors::GrigioScuro);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::GrigioChiaro);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Bianco);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	gluSphere(sphere, 2.0, 32, 16);
	
}

vector<GLuint>& Pallina::getBallTextures(void) { return this->ballTextures; }

GLUquadric* Pallina::getSphere(void) { return this->sphere; }