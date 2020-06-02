#include "Monete.h"

Monete::Monete()
{
	this->R = 255.0;
	this->G = 255.0;
	this->B = 0.0;
	this->dim = 2.0;
};


void Monete::drawObject(void)
{
	glColor3f(R, G, B);
	glutSolidCube(dim);
	cout << "drawObject Monete" << endl;
}
