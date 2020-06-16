#include "GameWindow.h"
#include "MenuManager.h"
#include "Utente.h"

Utente* Utente::instance = 0;

/*
	implementazione del pattern Singleton
*/
Utente* Utente::getInstance()
{
	if (instance == 0)
		instance = new Utente();
	
	return instance;
}

/* 
	costruttore: setta il parametro punteggio e carica dal file i dati per la dashboard
*/
Utente::Utente() 
{ 
	punteggio = 0.0;  
	prezzo_texture_1 = 10;
	prezzo_texture_2 = 20;
	prezzo_texture_3 = 30;

	gameOver = 0;
	vite = 4;
	
	caricaFile();
	
}

/*
	incrementaPunteggio: metodo utile per incrementare il punteggio durante il gioco e per settare in caso affermativo il nuovo high score.
*/
float Utente::incrementaPunteggio(void) 
{ 
	punteggio += 0.1;

	if (punteggio > punteggioMassimo)
		punteggioMassimo = punteggio;

	return (int)punteggio; 
}

/*
	caricaFile: metodo utile per caricare dal file i dati da mostrare all'utente.
				I dati comprendono: punteggio massimo, monete e stato delle texture: 0 se da acquistare, 1 se acquistata 2 se in uso.
				La texture in uso è passata alla pallina per poter essere applicata.
				In caso di errore ritorna il codice 19.
*/
void Utente::caricaFile(void)
{	
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
}

/*
	salvaFile: metodo utile per memorizzare i dati attuali su file
*/

void Utente::salvaFile(void)
{	
	ofstream fileWrite("file.txt");
	
	fileWrite << texture_1 << endl;
	fileWrite << texture_2<< endl;
	fileWrite << texture_3 << endl;

	fileWrite << monete << endl;
	fileWrite << punteggioMassimo;

	fileWrite.close();
	
}

/*
	eliminaVita: il metodo decrementa il numero di vite attuali, quando finiscono salva su file i dati e restituisce il codice 69.
*/
void Utente::eliminaVita(void)
{
	vite--;
	if (vite == 0)
		GameOver();
}

/*
	drawVite: il metodo prende come parametri le coordinate dove occorre disenare le vite e le disegna
			  sotto forma di cubi e applicando dei material.
*/
void Utente::drawVite(float x, float y, float z)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, Colors::RossoTenue);
	glMaterialfv(GL_FRONT, GL_EMISSION, Colors::Rosso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Colors::Nero);

	// TODO: Ruotare le vite, altrimenti non sono dritte
	for (int i = 0; i < vite; i++)
	{
		glPushMatrix();
			glTranslatef(x + i * 2, y, z + i * 2);
			glRotatef(-20, 1, 0, 1);
			glutSolidCube(1.0);
		glPopMatrix();
	}
}

/*
	textureAttiva: il metodo ritorna il numero della texture attualmente in uso (1, 2 o 3), oppure 0 in caso di errore
*/

int Utente::textureAttiva(void)
{
	if (texture_1 == 2) return 1;
	if (texture_2 == 2) return 2;
	if (texture_3 == 2) return 3;
	
	return 0;
}

/*
	textureComprate: il metodo prende come parametro il numero della texture che si vuole controllare.
					 Ritorna true se la texture è già stata acquistata, altrimenti ritorna false
*/

bool Utente::textureComprate(int texture)
{
	if (texture == 1 && texture_1 == 1) return true;
	if (texture == 2 && texture_2 == 1) return true;
	if (texture == 3 && texture_3 == 1) return true;

	return false;
}

/*
	compraTexture: data una texture il metodo la acquista se il numero di monete in possesso è sufficiente:
				   In caso positivo imposta a 1 la flag della texture, salva sul file e ritorna true. 
				   In caso di errore ritorna false.
*/

bool Utente::compraTexture(int texture)
{
	if (texture == 1 && (monete - prezzo_texture_1) >= 0) 
	{ 
		monete -= prezzo_texture_1;
		texture_1 = 1; 
		salvaFile();
		
		return true; 
	}
	if (texture == 2 && (monete - prezzo_texture_2) >= 0)
	{ 
		monete -= prezzo_texture_2;
		texture_2 = 1; 
		salvaFile(); 
		
		return true;
	}
	if (texture == 3 && (monete - prezzo_texture_3) >= 0)
	{ 
		monete -= prezzo_texture_3;
		texture_3 = 1; 
		salvaFile(); 
		
		return true;
	}

	return false;
}

/*
	scegliTexture: il metodo prende in input una texture e la imposta come in uso (flag = 2).
				   Se la texture è già stata acuistata completa l'operazione salvando su file, 
				   settando la texture precedentemente in uso a acquistata (flag = 1) e ritornando true.
				   In caso di errore ritorna false.
*/
bool Utente::scegliTexture(int texture)
{
	if (texture == 1 && texture_1 == 1) 
	{ 
		texture_1 = 2; 
		if (texture_2 == 2) texture_2 = 1;
		if (texture_3 == 2) texture_3 = 1;
		salvaFile();

		return true; 
	}
	if (texture == 2 && texture_2 == 1) 
	{ 
		texture_2 = 2; 
		if (texture_1 == 2) texture_1 = 1;
		if (texture_3 == 2) texture_3 = 1;
		salvaFile(); 
		
		return true; 
	}
	if (texture == 3 && texture_3 == 1) 
	{ 
		texture_3 = 2; 
		if (texture_1 == 2) texture_1 = 1;
		if (texture_2 == 2) texture_2 = 1;
		salvaFile(); 
		
		return true; 
	}

	return false;
}

/*
	incrementaMonete: il metodo incrementa il numero di monete disponibili nel gioco.
*/
void Utente::incrementaMonete(void) { monete++; }

/*
	metodi getter
*/
float Utente::getPunteggioMassimo(void) { return punteggioMassimo; }
int Utente::getMonete(void) { return monete; }
int Utente::getVite(void) { return vite; }
int Utente::getGameOver(void) { return gameOver; }

void Utente::resetGame(void)
{ 
	delete instance;
	instance = NULL;
}

void Utente::GameOver(void)
{
	salvaFile();
	gameOver = 1;
	SoundManager::getInstance()->resetMusic();
	glutDestroyWindow(GameWindow::getWindowId());
	
	Platforms::resetInstance();
	Pallina::resetInstance();

	MenuManager::start();
	
}