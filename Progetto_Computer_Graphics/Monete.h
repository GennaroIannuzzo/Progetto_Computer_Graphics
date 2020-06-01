#pragma once
#include "Oggetto.h"
class Monete : public Oggetto
{
	// costruttori
	Monete();
	Monete(GLfloat R, GLfloat G, GLfloat B, GLint dim);

	// Override metodo drowing
	void drawObject(void) override;
};

