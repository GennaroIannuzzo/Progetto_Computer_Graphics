#include "Pallina.h"

using namespace std;

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
}

Pallina::Pallina(int valDifficolta) : Pallina() 
{
	speed = 0.1;
	difficolta = valDifficolta;
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

void Pallina::incrementSpeed(void) { if(speed < 1.2) speed += 0.1; }

void Pallina::setTexture(string texture)
{
	cout << "la texture scelta e' " << texture << endl;
}

void Pallina::drawObject(void) {
	glColor3f(R, G, B);
	glTranslatef(posizione.getX(), posizione.getY(), posizione.getZ());
	glutSolidSphere(dim, (int)dim*6, (int)dim*6);
}