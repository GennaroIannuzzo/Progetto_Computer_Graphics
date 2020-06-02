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
	// cout << "drawObject Ostacolo" << endl;
}

void Ostacolo::Trigger(void)
{
	// cout << "Il tuo punteggio -> " << Ball_Manager::getInstance()->getBall().salvaPunteggio();
	cout << "Ho toccato un ostacolo!" << endl;
	exit(1);
}
