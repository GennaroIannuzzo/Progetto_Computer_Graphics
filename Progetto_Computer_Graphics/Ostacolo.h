#pragma once
#include "Oggetto.h"
class Ostacolo : public Oggetto
{
public:

	// costruttori
	Ostacolo();

	// Override metodo drowing
	void drawObject(void) override;
};

