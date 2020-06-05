#include "Utente.h"

Utente* Utente::instance = 0;


Utente* Utente::getInstance()
{
	if (instance == 0)
		instance = new Utente();
	
	return instance;
}

Utente::Utente() 
{ 
	punteggio = 0.0;  
	
	caricaFile();
	
}

float Utente::incrementaPunteggio(void) 
{ 
	punteggio += 0.1;

	if (punteggio > punteggioMassimo)
		punteggioMassimo = punteggio;

	return (int)punteggio; 
}

float Utente::getPunteggioMassimo(void) { return punteggioMassimo; }

int Utente::getMonete(void) { return monete; }
int Utente::getVite(void) { return vite; }

void Utente::caricaFile(void)
{
	/*
	- texture pallina
	- monete
	- punteggioMassimo
	
*/

	string texturePallina = "textureProva";

	ifstream file("file.txt");
	if (file)
	{
		string strMonete, strPunteggioMassimo;
		file >> texturePallina >> strMonete >> strPunteggioMassimo;
		
		monete = strtol(strMonete.c_str(), 0, 10);
		punteggioMassimo = strtol(strPunteggioMassimo.c_str(), 0, 10);
		
		file.close();
		
	}
	else
	{
		cout << "file inesistente" << endl;
		exit(19);
	}

	Pallina::getInstance()->setTexture(texturePallina);

}

void Utente::incrementaMonete(void) { monete++; }

void Utente::salvaFile(void)
{
	// salviamo i dati del punteggio e del punteggio massimo
	// rileggo la texure
	string texturePallina;
	ifstream fileRead("file.txt");
	
	fileRead >>  texturePallina;

	fileRead.close();

	// scrivo su file i dati del punteggio
	ofstream fileWrite("file.txt");
	
	fileWrite << texturePallina << endl;
	fileWrite << monete << endl;
	fileWrite << punteggioMassimo;

	fileWrite.close();
	
}

void Utente::salvaFile(string texture)
{
	// leggo il punteggio massimo e le monete
	string oldTexture;
	ifstream fileRead("file.txt");

	fileRead >> oldTexture >> monete >> punteggioMassimo;

	fileRead.close();

	// scrivo su file i dati per aggiornare la nuova texture
	ofstream fileWrite("file.txt");
	fileWrite << texture << endl;
	fileWrite << monete << endl;
	fileWrite << punteggioMassimo;

	fileWrite.close();
}

void Utente::setDifficolta(int diff) 
{ 
	// vite = 5 - diff;
	vite = 4;
}

void Utente::eliminaVita(void)
{
	cout << "vite rimantenti " << vite - 1 << endl;
	vite--;
	if (vite == 0)
	{
		salvaFile();
		exit(69);
	}
}

void Utente::drawMonete(float x, float y, float z)
{
	glColor3f(255.0, 255.0, 0.0);
	glTranslatef(x, y, z);
	glutSolidCube(1.0);
}

void Utente::drawVite(float x, float y, float z)
{
	glColor3f(255.0, 0.0, 255.0);
	for (int i = 0; i < vite; i++)
	{
		glPushMatrix();
			glTranslatef(x + i*2, y, z);
			glutSolidCube(1.0);
		glPopMatrix();
	}
}