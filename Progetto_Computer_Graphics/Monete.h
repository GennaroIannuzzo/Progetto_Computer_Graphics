#pragma once
#include "Oggetto.h"
#include "Utente.h"
#include "soil.h"

class Monete : public Oggetto
{
private:
	
	static GLuint textureMoneta;
	static GLUquadric* disk;

	void Trigger(void);
	int angolo;

public:
	// costruttori
	Monete();

	// Override metodo drowing
	void drawObject(void) override;
	void drawObject(float x, float y, float z);
	
	static GLuint& getTextureMoneta(void);
	static void setTextureMoneta(void);
	static GLUquadric* getDisk(void);

};

