#include "Pallina.h"

using namespace std;

// Attributi Statici
GLfloat Pallina::dim = 2;
GLfloat Pallina::R = 0.0;
GLfloat Pallina::G = 0.0;
GLfloat Pallina::B = 255.0;

// Costruttore
Pallina::Pallina() {}

Pallina::Pallina(int valDifficolta) {
	posizione = Punto(0.0, 20.0, 0.0);
	speed = 0.1;
	difficolta = valDifficolta;
	movimento = 0;
}

// Getter
Punto Pallina::getPosizione(void) {
	return posizione;
}

// Metodi
void Pallina::moveBall(void) {
	if (movimento == 0)
		posizione.setZ(posizione.getZ() - speed);
	else
		posizione.setX(posizione.getX() + speed);

	glutPostRedisplay();
}

void Pallina::moveLeft(void) {
	posizione.setZ(posizione.getZ() - speed);
	movimento = 0;
	glutPostRedisplay();
}

void Pallina::moveRight(void) {
	posizione.setX(posizione.getX() + speed);
	movimento = 1;
	glutPostRedisplay();
}

void Pallina::incrementSpeed() {
	if(speed < 1.2)
		speed += 0.1;

	cout << "speed -> " << speed << endl;
}

void Pallina::drawPallina(void) {
	glColor3f(R, G, B);
	glTranslatef(posizione.getX(), posizione.getY(), posizione.getZ());
	glutSolidSphere(dim, (int)dim*6, (int)dim*6);
}