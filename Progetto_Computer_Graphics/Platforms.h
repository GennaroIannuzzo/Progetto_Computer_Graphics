#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Piattaforma.h"

using namespace std;

class Platforms
{
private:

	// Attributi
	vector<Piattaforma> platforms;
	static Punto lastPoint;
	static GLint fallenPlatforms;

public:

	// Costruttori
	Platforms();

	// Getter
	vector<Piattaforma> getPlatforms(void);
	Punto getLastPoint(void);
	GLint getFallenPlatforms(void);
	
	// Setter
	void setFallenPlatforms(GLint);

	// Metodi
	void generaNuovaPiattaforma(void);
	void drawPlatforms(void);
	void triggerPlatform(void);
	
	// Distruttore
	~Platforms();
};