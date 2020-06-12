#pragma once
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

class Punto
{
private:

	// Attributi
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

	// Overload Operatori
	Punto operator+(const Punto&);

	// Metodi
	void printPoint(void);

	// Distruttore
	~Punto();
};