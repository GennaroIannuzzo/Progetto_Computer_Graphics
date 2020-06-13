#include "Monete.h"

GLUquadric* Monete::disk = gluNewQuadric();
GLuint Monete::textureMoneta = 0;

Monete::Monete()
{
	this->R = 255.0;
	this->G = 255.0;
	this->B = 0.0;
	this->dim = 2.0;
	this->angolo = 0;
};

void Monete::drawObject(void)
{
	// glColor3f(R, G, B);
	angolo = (angolo + 1) % 360;
	glRotatef(angolo, 0, 1, 0);
	
	glBindTexture(GL_TEXTURE_2D, textureMoneta);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::GialloOcraTenue);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::GialloOcra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Nero);

	gluDisk(disk, 0, 1.0, 20.0, 20.0);
	// glutSolidCube(dim);
}

void Monete::Trigger(void)
{
	Utente::getInstance()->incrementaMonete();
}

void Monete::drawObject(float x, float y, float z)
{
	this->dim = 1.0;
	glTranslatef(x, y, z);
	glRotatef(45, 1, 0, 0);
	drawObject();
}

GLuint& Monete::getTextureMoneta(void) { return textureMoneta; }

void Monete::setTextureMoneta(void)
{
	textureMoneta = SOIL_load_OGL_texture(
		"Textures/Moneta/images.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

GLUquadric* Monete::getDisk(void) { return disk; }