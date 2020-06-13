#include "Ostacolo.h"

Ostacolo::Ostacolo() 
{
	this->R = 0.0;
	this->G = 0.0;
	this->B = 0.0;
	this->dim = 2.0;
}

void Ostacolo::drawObject(void)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Bianco);

	glutSolidCube(dim);
}

void Ostacolo::Trigger(void)
{
	cout << "Ho toccato un ostacolo!" << endl;
	SoundManager::getInstance()->hurdleMusic();
	Utente::getInstance()->eliminaVita();
}
