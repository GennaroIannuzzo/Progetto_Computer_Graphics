#include <iostream>
#include <fstream>
#include <cstdlib>
// #include "Ball_Manager.h"

using namespace std;

#pragma once
class Utente
{
	static Utente* instance;

	float punteggio;
	float punteggioMassimo;

	int monete;

	// Costruttori
	Utente();

	void caricaFile(void);

public:
	static Utente* getInstance();

	float incrementaPunteggio(void);
	float getPunteggioMassimo(void);
	void incrementaMonete(void);

	void salvaFile(void);
	void salvaFile(string texture);	// per memorizzare la texture acquistata

};

