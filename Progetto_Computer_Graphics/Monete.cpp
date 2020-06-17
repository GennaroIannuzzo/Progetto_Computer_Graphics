#include "Monete.h"

GLUquadric* Monete::disk = gluNewQuadric();
GLuint Monete::textureMoneta = 0;

Monete::Monete()
{
	this->dim = 1.0;
	this->angolo = 0;
};

/*	drawObject: Il metodo disegna l'oggetto e vi applica i material e la texture.
 *		La moneta ruoterà durante il gioco.
 */
void Monete::drawObject(void)
{
	angolo = (angolo + 1) % 360;
	glRotatef(angolo, 0, 1, 0);
	
	glBindTexture(GL_TEXTURE_2D, textureMoneta);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::GialloOcraTenue);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::GialloOcra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Nero);

	gluDisk(disk, 0, dim, 20.0, 20.0);
}

/*	drawObject: il metodo consente di disegnare un oggetto richiamando il metodo drawObject ma
 *	effettuando una traslazione dell'oggetto. Tale soluzione risulta necessaria per disegnare la
 *	moneta simbolo del punteggio e di permettere che essa segua il giocatore durante la partita.
 */
void Monete::drawObject(float x, float y, float z)
{
	glTranslatef(x, y, z);
	glRotatef(45, 1, 0, 0);
	drawObject();
}

/* Trigger: la gestione dell'evento prevede di incrementare il numero delle monete nella dashboard dell'utente. */
void Monete::Trigger(void)
{
	SoundManager::getInstance()->coinMusic();
	Utente::getInstance()->incrementaMonete();
}

/* setTextureMoneta: Il metodo consente di applicare la texture alla moneta utilizzando la libreira SOIL. */
void Monete::setTextureMoneta(void)
{
	textureMoneta = SOIL_load_OGL_texture(
		"Textures/Moneta/images.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

// getter
GLuint& Monete::getTextureMoneta(void) { return textureMoneta; }

GLUquadric* Monete::getDisk(void) { return disk; }