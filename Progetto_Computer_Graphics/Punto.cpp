#include "Punto.h"

// Costruttori
Punto::Punto() {}

Punto::Punto(GLfloat valx, GLfloat valy, GLfloat valz)
{
	x = valx;
	y = valy;
	z = valz;
}

// Getter
GLfloat Punto::getX() { return x; }
GLfloat Punto::getY() { return y; }
GLfloat Punto::getZ() { return z; }

// Setter
void Punto::setX(GLfloat valx) { x = valx; }
void Punto::setY(GLfloat valy) { y = valy; }
void Punto::setZ(GLfloat valz) { z = valz; }

// Overload Operatori
Punto Punto::operator+(const Punto& b) 
{
	Punto p;

	p.x = this->x + b.x;
	p.y = this->y + b.y;
	p.z = this->z + b.z;

	return p;
}

// Metodi
void Punto::printPoint(void) { cout << "x: " << x << "y: " << y << "z: " << z << endl; }

// Distruttori
Punto::~Punto() {};