#include "Ostacolo.h"

Ostacolo::Ostacolo() {};

Ostacolo::Ostacolo(GLfloat R, GLfloat G, GLfloat B, GLint dim)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->dim = dim;
}

void Ostacolo::drawObject(void)
{
	cout << "drawObject Ostacolo" << endl;
}
