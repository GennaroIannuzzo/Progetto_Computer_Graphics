#pragma once
#include "Oggetto.h"
// #include "Ball_Manager.h"

class Ostacolo : public Oggetto
{
public:

	// costruttori
	Ostacolo();

	// Override metodo drowing
	void drawObject(void) override;
	void Trigger(void);
};

