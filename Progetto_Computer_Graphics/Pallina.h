/*	classe Pallina:	La classe Singleton disegna la pallina La classe eredita dalla classe Oggetto */
#include <vector>
#include <iostream>
#include "Punto.h"
#include "Oggetto.h"
#include "Colors.h"
#include "soil.h"

#pragma once
class Pallina : public Oggetto
{
private:
	
	static Pallina* instance;
	
	// Attributi
	GLfloat speed;
	GLuint ballTextures;
	int movimento;
	int punteggio;
	int angolo;
	GLUquadric* sphere;

	// Costruttore
	Pallina();

public:

	static Pallina* getInstance();
	
	// Metodi
	void moveBall(void); 
	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	
	void setTexture(string stringa);
	
	void drawObject(void) override;

	GLUquadric* getSphere(void);

	static void resetInstance(void);
};