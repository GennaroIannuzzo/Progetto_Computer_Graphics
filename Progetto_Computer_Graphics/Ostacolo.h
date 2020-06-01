#pragma once
#include "Oggetto.h"
class Ostacolo : public Oggetto
{
public:

	// costruttori
	Ostacolo();
	Ostacolo(GLfloat R, GLfloat G, GLfloat B, GLint dim);

	// Override metodo drowing
	void drawObject(void) override;
};

