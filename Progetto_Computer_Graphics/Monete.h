#pragma once
#include "Oggetto.h"
#include "Utente.h"

class Monete : public Oggetto
{
private:
	void Trigger(void);

public:
	// costruttori
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
	
};

