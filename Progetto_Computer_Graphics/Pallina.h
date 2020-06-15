/*
	classe Pallina:	La classe Singleton disegna la pallina. 
					La classe eredita dalla classe Oggetto
*/
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

	// Costruttore
	Pallina();

public:

	static Pallina* getInstance();
	
	// Metodi
	void moveBall(void); 
	void moveLeft(void);
	void moveRight(void);
	void incrementSpeed(void);
	
	void setTexture(int textureAttiva); 
	void setDifficolta(int diff); // ##
	
	void drawObject(void) override;
	
	vector<GLuint>& getBallTextures(void);
	GLUquadric* getSphere(void);
};