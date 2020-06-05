#include "Punto.h"
#include "Oggetto.h"
#include <iostream>

#pragma once
class Pallina : public Oggetto
{
private:
	
	static Pallina* instance;
	// Attributi
	GLfloat speed;
	int movimento;
	int difficolta;
	int punteggio;
	
	// Costruttori
	Pallina();
	// Pallina(int difficolta);

public:

	// Metodi
	static Pallina* getInstance();

	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	void moveBall(void);
	void drawObject(void) override;
	void setTexture(string texture);
	void setDifficolta(int diff);
};