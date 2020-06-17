/*
 *	classe SoundManager: La classe fornisce la possibilità di inserire la musica nel gioco.
 *		La classe è implementata come Singleton per avere un'unica istanza durante tutta la partita.
*/

#pragma once
#include <irrKlang.h>

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class SoundManager
{
	static SoundManager* instance;

	ISoundEngine* engine;

	// costruttore
	SoundManager();

public:
	static SoundManager* getInstance();

	void gameMusic(void);			// musica di gioco
	void hurdleMusic(void);			// musica quando si tocca un ostacolo
	void coinMusic(void);			// musica quando si tocca una moneta

	void resetMusic(void);			// reset della musica
};

