#pragma once
#include "Oggetto.h"
#include "Utente.h"

class Monete : public Oggetto
{
private:
	void Trigger(void);
	int angolo;

public:
	// costruttori
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
	void drawObject(float x, float y, float z);
	
};

