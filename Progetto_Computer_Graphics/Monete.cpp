#include "Monete.h"

Monete::Monete() {};

Monete::Monete(GLfloat R, GLfloat G, GLfloat B, GLint dim)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->dim = dim;
}

void Monete::drawObject(void)
{
	cout << "drawObject Monete" << endl;
}
