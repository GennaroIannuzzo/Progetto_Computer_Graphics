/*
	Classe punto: La classe Punto definisce un dipo di dato derivato 3d con metodi per settare e ritornare le varie coordinate.

*/
#pragma once
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

class Punto
{
private:

	GLfloat x;
	GLfloat y;
	GLfloat z;

public:

	// Costruttori
	Punto();
	Punto(GLfloat valx, GLfloat valy, GLfloat valz);

	// Getter
	GLfloat getX();
	GLfloat gety();
	GLfloat getZ();

	// Setter
	void setX(GLfloat valx);
	void sety(GLfloat valy);
	void setZ(GLfloat valz);

	// Overload Operatore + 
	Punto operator+(const Punto&);

	// Distruttore
	~Punto();
};