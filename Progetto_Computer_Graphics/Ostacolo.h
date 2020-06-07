#pragma once
#include "Oggetto.h"
#include "Utente.h"

class Ostacolo : public Oggetto
{
private:
	void Trigger(void);

public:

	// costruttori
	Ostacolo();

	// Override metodo drowing
	void drawObject(void) override;
	
};

