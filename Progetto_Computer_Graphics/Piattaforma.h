#pragma once
#include "Oggetto.h"
// #include "Punto.h"
#include <iostream>
#include <cstdlib>

class Piattaforma : public Oggetto {

public:

	// Costruttori
	Piattaforma();
	Piattaforma(Punto valPunto);

	// Metodi
	void drawObject(void) override;

	// Distruttore
	~Piattaforma();
};