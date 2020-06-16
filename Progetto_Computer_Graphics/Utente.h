/*
	classe Utente: contiene le principali funzionalità utili a gestire la dashboard del giocatore.
				   La classe è implementata come Singleton per avere un'unica istanza durante il gioco.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Pallina.h"


using namespace std;

#pragma once
class Utente
{
	static Utente* instance;

	float punteggio;			// punteggio corrente
	float punteggioMassimo;		// punteggio massimo

	int monete;					// monete totali disponibili
	int vite;					// vite disponibili
	int gameOver;				// gioco terminato
	
	// stato delle texture: 0 se non acquistata, 1 se acquistata, 2 se in uso
	int texture_1;				
	int texture_2;
	int texture_3;

	// prezzo delle texture
	int prezzo_texture_1;
	int prezzo_texture_2;
	int prezzo_texture_3;

	Utente();					// Costruttore

	void caricaFile(void);		// caricamento punteggi e stato delle texture

public:

	static Utente* getInstance();	// ritorna l'istanza della classe Singleton
	
	// metodi Getter
	int   getMonete(void);
	int   getVite(void);
	float getPunteggioMassimo(void);
	int   getGameOver(void);

	void  resetGame(void);

	void  eliminaVita(void);			// metodo per eliminare una vita

	float incrementaPunteggio(void);	// metodo utile per incrementare il punteggio attuale
	
	void  incrementaMonete(void);		// metodo per incrementare il numero attuale di monete

	void  salvaFile(void);				// metodo per memorizzare i dati della dashboard su file

	int   textureAttiva(void);			// ritorna quale texture è attualmente attiva
	bool  textureComprate(int texture); // ritorna true se la texture è stata già acquistata
	bool  compraTexture(int texture);	// setta come acquistata una texture
	bool  scegliTexture(int texture);	// setta come attiva una texture
	void  GameOver(void);				// metodo per uscire dal gioco

	void  drawVite(float x, float y, float z);	// metodo per disegnare le vite 

	

};

