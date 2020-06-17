#include "Ostacolo.h"

Ostacolo::Ostacolo() 
{
	this->dim = 4.0;
}

/* drawObject: il metodo disegna l'ostacolo come cubo e vi applica il material */
void Ostacolo::drawObject(void)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::Nero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Nero);

	glutSolidCube(dim);
}

/* Trigger: il metodo decrementa il numero di vite dell'utente e genera un feedback audio */
void Ostacolo::Trigger(void)
{
	SoundManager::getInstance()->hurdleMusic();
	Utente::getInstance()->eliminaVita();
}
