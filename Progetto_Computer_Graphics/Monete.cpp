#include "Monete.h"

Monete::Monete()
{
	this->R = 255.0;
	this->G = 255.0;
	this->B = 0.0;
	this->dim = 2.0;
	this->angolo = 0;
};

void Monete::drawObject(void)
{
	glColor3f(R, G, B);
	angolo = (angolo + 1) % 360;
	glRotatef(angolo, 0, 1, 0);
	glutSolidCube(dim);
}

void Monete::Trigger(void)
{
	Utente::getInstance()->incrementaMonete();
}

void Monete::drawObject(float x, float y, float z)
{
	this->dim = 1.0;
	glTranslatef(x, y, z);
	glRotatef(45, 0, 1, 0);
	drawObject();
}
