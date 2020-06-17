/*	classe Monete: La classe eredita dalla classe Oggetto. 
 *		La classe ha il compito di disegnare le monete nel gioco e 
 *		digestire l'evento con la collisione.
 */
#pragma once
#include "Oggetto.h"
#include "Utente.h"
#include "soil.h"

class Monete : public Oggetto
{
private:
	// attributi per la gestione delle texture
	static GLuint textureMoneta;
	static GLUquadric* disk;
	
	int angolo;
	
	void Trigger(void);	// incremento numero di monete

public:
	
	// costruttore
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
	void drawObject(float x, float y, float z);	// disegno in determinate coordinate
	
	// gestione texture
	static GLuint& getTextureMoneta(void);
	static void setTextureMoneta(void);
	static GLUquadric* getDisk(void);

};

