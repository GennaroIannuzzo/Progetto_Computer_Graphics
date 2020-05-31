#include "Platforms.h"

using namespace std;

// Attributi
Punto Platforms::lastPoint = Punto(0.0, 0.0, 0.0);
GLint Platforms::fallenPlatforms = 0;

// Costruttori
Platforms::Platforms()
{
	platforms.push_back(Piattaforma(Punto(0.0, 0.0, 0.0)));
	srand((unsigned)time(NULL));

	for (int i = 1; i < 3; i++) {
		generaNuovaPiattaforma();
	}
}

// Getter
vector<Piattaforma> Platforms::getPlatforms(void) {
	return platforms;
}

Punto Platforms::getLastPoint(void) {
	Punto app = Punto(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());

	if (platforms[0].getPunto().getX() == 0.0 && platforms[0].getPunto().getY() == 0.0 && platforms[0].getPunto().getZ() == 0.0)
		return lastPoint;
	else
		app = app + platforms[0].getPunto();

	return app;
}

GLint Platforms::getFallenPlatforms(void) {
	return fallenPlatforms;
}

// Setter
void Platforms::setFallenPlatforms(GLint valFallenPlatforms) { fallenPlatforms = valFallenPlatforms; }

// Metodi
void Platforms::generaNuovaPiattaforma(void)
{
	// In alto
	if (rand() % 2 == 0) {
		platforms.push_back(Piattaforma(Punto(Piattaforma::getDim(), 0.0, 0.0)));
	}

	else {
		platforms.push_back(Piattaforma(Punto(0.0, 0.0, -Piattaforma::getDim())));
	}
	
	// platforms.push_back(Piattaforma(Punto(0.0, 0.0, -Piattaforma::getDim())));
}

void Platforms::triggerPlatform(void)
{
	// platforms.front().animazione();
	generaNuovaPiattaforma();
	lastPoint = lastPoint + platforms.front().getPunto();
	// Simula Caduta
	platforms.erase(platforms.begin());
	fallenPlatforms++;
}

void Platforms::drawPlatforms(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glTranslatef(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());

	for (auto it = platforms.begin(); it != platforms.end(); ++it)
	{
		if (it == platforms.begin())
			glColor3f(0.0, 255.0, 0.0);
		else
			glColor3f(255.0, 0.0, 0.0);
		it->drawPiattaforma();
	}
}

// Distruttore
Platforms::~Platforms() {};
