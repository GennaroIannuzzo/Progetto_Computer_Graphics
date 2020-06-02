#include "Ostacolo.h"

Ostacolo::Ostacolo() 
{
	this->R = 0.0;
	this->G = 255.0;
	this->B = 255.0;
	this->dim = 2.0;
}

void Ostacolo::drawObject(void)
{
	glColor3f(R, G, B);
	glutSolidCube(dim);
	cout << "drawObject Ostacolo" << endl;
}
