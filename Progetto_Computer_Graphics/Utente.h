#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Pallina.h"
 
using namespace std;

#pragma once
class Utente
{
	static Utente* instance;

	float punteggio;
	float punteggioMassimo;

	int monete;
	int vite;

	// Costruttori
	Utente();

	void caricaFile(void);

public:
	static Utente* getInstance();
	void setDifficolta(int diff);
	void eliminaVita(void);

	float incrementaPunteggio(void);
	float getPunteggioMassimo(void);
	int   getMonete(void);
	int   getVite(void);
	void incrementaMonete(void);

	void salvaFile(void);
	void salvaFile(string texture);	// per memorizzare la texture acquistata

	void drawMonete(float x, float y, float z);
	void drawVite(float x, float y, float z);
};

