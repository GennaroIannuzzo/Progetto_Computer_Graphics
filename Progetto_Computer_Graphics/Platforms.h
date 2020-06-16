#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Piattaforma.h"

using namespace std;

class Platforms
{
private:

	static Platforms* instance;

	// Costruttori
	Platforms();

	// Attributi
	vector<Piattaforma> platforms;
	Punto lastPoint;
	GLint fallenPlatforms;
	
	void generaNuovaPiattaforma(void);

public:

	// Getter
	static Platforms* getInstance();
	vector<Piattaforma>& getPlatforms(void);
	Punto getLastPoint(void);
	GLint getFallenPlatforms(void);
	
	// Setter
	void setFallenPlatforms(GLint);
	
	// Metodi
	void drawPlatforms(void);
	void triggerPlatform(void);
	
	static void resetInstance(void);
};