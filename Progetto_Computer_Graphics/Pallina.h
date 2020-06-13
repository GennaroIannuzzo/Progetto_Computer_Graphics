#include "Punto.h"
#include "Oggetto.h"
#include "Colors.h"
#include <vector>
#include <iostream>

#pragma once
class Pallina : public Oggetto
{
private:
	
	static Pallina* instance;
	
	// Attributi
	GLfloat speed;
	vector<GLuint> ballTextures;
	int movimento;
	int difficolta;
	int punteggio;
	int angolo;
	int indiceTexture;
	GLUquadric* sphere;

	// Costruttori
	Pallina();

public:

	// Metodi
	static Pallina* getInstance();

	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	void moveBall(void);
	void drawObject(void) override;
	void setTexture(int textureAttiva);
	void setDifficolta(int diff);
	vector<GLuint>& getBallTextures(void);
	GLUquadric* getSphere(void);
};