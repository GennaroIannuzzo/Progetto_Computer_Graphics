#pragma once
#include "Oggetto.h"
#include "Utente.h"

// #include "Ball_Manager.h"

class Monete : public Oggetto
{
public:
	// costruttori
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
	void Trigger(void);
};

