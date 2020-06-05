#pragma once
#include "Oggetto.h"
#include "Monete.h"
#include "Ostacolo.h"
#include <iostream>
#include <cstdlib>

class Piattaforma : public Oggetto 
{

public:

	// Costruttori
	Piattaforma();
	Piattaforma(Punto valPunto);

	Oggetto* getOggetto(void);
	int getTipo(void);

	// Metodi
	void drawObject(void) override;
	void dropOggetto(void);

	// Distruttore
	~Piattaforma();

private:
	Oggetto* oggetto;
	int tipo;

	void calcolaPosizione(GLfloat& x, GLfloat& y, GLfloat& z);
};