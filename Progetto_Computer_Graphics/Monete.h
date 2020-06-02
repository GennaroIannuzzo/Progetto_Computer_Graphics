#pragma once
#include "Oggetto.h"
class Monete : public Oggetto
{
public:
	// costruttori
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
};

