#include "Platforms.h"

using namespace std;

Platforms* Platforms::instance = 0;

// Costruttori
Platforms::Platforms()
{
	// Attributi
	lastPoint = Punto(0.0, 0.0, 0.0);
	fallenPlatforms = 0;

	platforms.push_back(Piattaforma(Punto(0.0, 0.0, 0.0)));
	srand((unsigned)time(NULL));

	for (int i = 1; i < 10; i++) {
		generaNuovaPiattaforma();
	}
}

// Getter
Platforms* Platforms::getInstance()
{
	if (instance == 0)
		instance = new Platforms();

	return instance;
}

vector<Piattaforma>& Platforms::getPlatforms(void) { return platforms; }

Punto Platforms::getLastPoint(void) 
{
	Punto app = Punto(lastPoint.getX(), lastPoint.gety(), lastPoint.getZ());

	if (platforms[0].getPosizione().getX() == 0.0 && platforms[0].getPosizione().gety() == 0.0 && platforms[0].getPosizione().getZ() == 0.0)
		return lastPoint;
	else
		app = app + platforms[0].getPosizione();

	return app;
}

GLint Platforms::getFallenPlatforms(void) 
{
	return fallenPlatforms;
}

// Setter
void Platforms::setFallenPlatforms(GLint valFallenPlatforms) { fallenPlatforms = valFallenPlatforms; }

// Metodi
void Platforms::generaNuovaPiattaforma(void)
{
	GLfloat dimension = platforms[0].getDim();

	// In alto
	if (rand() % 2 == 0)
		platforms.push_back(Piattaforma(Punto(dimension, 0.0, 0.0)));
	
	else
		platforms.push_back(Piattaforma(Punto(0.0, 0.0, -dimension)));
	
}

void Platforms::triggerPlatform(void)
{
	generaNuovaPiattaforma();
	lastPoint = lastPoint + platforms.front().getPosizione();
	
	platforms.erase(platforms.begin());
	fallenPlatforms++;
}

void Platforms::drawPlatforms(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glTranslatef(lastPoint.getX(), lastPoint.gety(), lastPoint.getZ());

	for (auto it = platforms.begin(); it != platforms.end(); ++it)
	{

		// if (it == platforms.begin())
		// 	glColor3f(0.0, 255.0, 0.0);
		// else
		// 	glColor3f(platforms.at(0).getR(), platforms.at(0).getG(), platforms.at(0).getB());
		
		it->drawObject();
	}
}

void Platforms::resetInstance()
{
	delete instance;
	instance = NULL;
}
