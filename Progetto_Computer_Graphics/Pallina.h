#include "Punto.h"
#include "Oggetto.h"
#include <iostream>

#pragma once
class Pallina : public Oggetto
{
private:
	
	// Attributi
	GLfloat speed;
	int movimento;
	int difficolta;
	int punteggio;
	
public:

	// Costruttori
	Pallina();
	Pallina(int difficolta);

	// Metodi
	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	void moveBall(void);
	void drawObject(void) override;
	void incrementaPunteggio(void);
	int salvaPunteggio(void);
};