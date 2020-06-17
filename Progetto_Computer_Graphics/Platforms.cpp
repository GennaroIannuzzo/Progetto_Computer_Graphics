#include "Platforms.h"

using namespace std;

// Istanza singola della classe
Platforms* Platforms::instance = 0;

// Costruttori
Platforms::Platforms()
{
	// Attributi
	lastPoint = Punto(0.0, 0.0, 0.0);
	fallenPlatforms = 0;
	limitPlatforms = 2;

	platforms.push_back(Piattaforma(Punto(0.0, 0.0, 0.0)));
	srand((unsigned)time(NULL));

	for (int i = 1; i < 10; i++) generaNuovaPiattaforma();
}

/* Restituisce l'istanza della classe e la crea se non esiste */
Platforms* Platforms::getInstance()
{
	if (instance == 0)
		instance = new Platforms();

	return instance;
}

/* Restituisce il vettore di piattaforme */
vector<Piattaforma>& Platforms::getPlatforms(void) { return platforms; }

/* Restituisce la posizione dell'ultima piattaforma all'interno del vettore */
Punto Platforms::getLastPoint(void) 
{
	Punto app = Punto(lastPoint.getX(), lastPoint.gety(), lastPoint.getZ());

	// Per le prime 10 piattaforme non aggiunge la posizione della piattaforma 0
	if (platforms[0].getPosizione().getX() == 0.0 && platforms[0].getPosizione().gety() == 0.0 && platforms[0].getPosizione().getZ() == 0.0)
		return lastPoint;
	else
		app = app + platforms[0].getPosizione();

	return app;
}

/* Dice se le piattaforme cadute hanno superato il limite di piattaforme per aggiornare la velocità */
bool Platforms::getFallenPlatforms(void) 
{
	// Quando viene superato, il limite viene raddoppiato
	if (fallenPlatforms > limitPlatforms)
	{
		limitPlatforms *= 2;
		return true;
	}
	return false;
}

/* Imposta il numero di piattaforme cadute */
void Platforms::setFallenPlatforms(GLint valFallenPlatforms) { fallenPlatforms = valFallenPlatforms; }

/* Genera una nuova piattaforma randomicamente a sinistra o a destra */
void Platforms::generaNuovaPiattaforma(void)
{
	GLfloat dimension = platforms[0].getDim();

	if (rand() % 2 == 0) platforms.push_back(Piattaforma(Punto(dimension, 0.0, 0.0)));
	else platforms.push_back(Piattaforma(Punto(0.0, 0.0, -dimension)));
}

/* Esecuzione del trigger relativo alla piattaforma */
void Platforms::triggerPlatform(void)
{
	// Genera una nuova piattaforma
	generaNuovaPiattaforma();

	// Aggiorna l'ultimo punto
	lastPoint = lastPoint + platforms.front().getPosizione();
	
	// Cancella la prima piattaforma dal vettore
	platforms.erase(platforms.begin());

	// Incrementa il numero di piattaforme cadute 
	fallenPlatforms++;
}

/* Disegna le piattaforme all'interno della scena */
void Platforms::drawPlatforms(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glTranslatef(lastPoint.getX(), lastPoint.gety(), lastPoint.getZ());

	for (auto it = platforms.begin(); it != platforms.end(); ++it) it->drawObject();
}

/* Effettua il reset dell'istanza */
void Platforms::resetInstance()
{
	delete instance;
	instance = NULL;
}
