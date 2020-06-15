/*
	Ostacolo: La classe ostacolo eredita da Oggetto e gestisce il disegno dell'ostacolo e 
			  l'evento leago alla collisione.
*/
#pragma once
#include "Oggetto.h"
#include "Utente.h"

class Ostacolo : public Oggetto
{
private:
	void Trigger(void);	// decrementa il numero di vite 

public:

	// costruttore
	Ostacolo();

	// Override metodo drowing
	void drawObject(void) override;
	
};

