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
	string texturePallina = "textureProva";

	ifstream file("file.txt");
	if (file)
	{
		string strMonete, strPunteggioMassimo, strTexture_1, strTexture_2, strTexture_3;

		file >> strTexture_1 >> strTexture_2 >> strTexture_3 >> strMonete >> strPunteggioMassimo;
		
		texture_1 = strtol(strTexture_1.c_str(), 0, 10);
		texture_2 = strtol(strTexture_2.c_str(), 0, 10);
		texture_3 = strtol(strTexture_3.c_str(), 0, 10);

		monete = strtol(strMonete.c_str(), 0, 10);
		punteggioMassimo = strtol(strPunteggioMassimo.c_str(), 0, 10);
		
		file.close();
		
	}
	else
	{
		cout << "file inesistente" << endl;
		exit(19);
	}

	// apportare le dovute modifiche
	Pallina::getInstance()->setTexture(texturePallina);

}

void Utente::incrementaMonete(void) { monete++; }

void Utente::salvaFile(void)
{
	// scrivo su file i dati del punteggio
	ofstream fileWrite("file.txt");
	
	fileWrite << texture_1 << endl;
	fileWrite << texture_2<< endl;
	fileWrite << texture_3 << endl;

	fileWrite << monete << endl;
	fileWrite << punteggioMassimo;

	fileWrite.close();
	
}

/*
void Utente::salvaFile(string texture)
{
	// leggo il punteggio massimo e le monete
	string strMonete, strPunteggioMassimo, strTexture_1, strTexture_2, strTexture_3;
	ifstream fileRead("file.txt");

	fileRead >> strTexture_1 >> strTexture_2 >> strTexture_3 >> strMonete >> strPunteggioMassimo;

	fileRead.close();

	// scrivo su file i dati per aggiornare la nuova texture
	ofstream fileWrite("file.txt");

	fileWrite << strTexture_1 << endl;
	fileWrite << strTexture_2 << endl;
	fileWrite << strTexture_3 << endl;

	fileWrite << monete << endl;
	fileWrite << punteggioMassimo;

	fileWrite.close();
}
*/

void Utente::setDifficolta(int diff) 
{ 
	vite = 5 - diff;
	
}

void Utente::eliminaVita(void)
{
	vite--;
	if (vite == 0)
	{
		salvaFile();
		exit(69);
	}
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

int Utente::textureAttiva(void)
{
	if (texture_1 == 2) return 1;
	if (texture_2 == 2) return 2;
	if (texture_3 == 2) return 3;
	
	return 0;
}

bool Utente::textureComprate(int texture)
{
	if (texture == 1 && texture_1 == 1) return true;
	if (texture == 2 && texture_2 == 1) return true;
	if (texture == 3 && texture_3 == 1) return true;

	return false;
}

bool Utente::compraTexture(int texture)
{
	if (texture == 1 && (monete - 10) >= 0) 
	{ 
		monete -= 10; 
		texture_1 = 1; 
		salvaFile();
		
		return true; 
	}
	if (texture == 2 && (monete - 20) >= 0) 
	{ 
		monete -= 20; 
		texture_2 = 1; 
		salvaFile(); 
		
		return true;
	}
	if (texture == 3 && (monete - 30) >= 0) 
	{ 
		monete -= 30; 
		texture_3 = 1; 
		salvaFile(); 
		
		return true;
	}

	return false;
}

bool Utente::scegliTexture(int texture)
{
	if (texture == 1 && texture_1 == 1) 
	{ 
		texture_1 = 2; 
		texture_2 = texture_3 = 1;
		salvaFile();

		return true; 
	}
	if (texture == 2 && texture_2 == 1) 
	{ 
		texture_2 = 2; 
		texture_1 = texture_3 = 1;
		salvaFile(); 
		
		return true; 
	}
	if (texture == 3 && texture_3 == 1) 
	{ 
		texture_3 = 2; 
		texture_1 = texture_2 = 1;
		salvaFile(); 
		
		return true; 
	}

	return false;
}