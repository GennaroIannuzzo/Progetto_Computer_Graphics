#include "SoundManager.h"

SoundManager* SoundManager::instance = 0;

SoundManager::SoundManager()
{
	engine = createIrrKlangDevice();
}

SoundManager* SoundManager::getInstance()
{
	if (instance == 0)
		instance = new SoundManager();

	return instance;
}

/*
	gameMusic: play musica di sottofondo con ripetizione continua
*/
void SoundManager::gameMusic(void) { engine->play2D("sound/getout6db.wav", true); }

/*
	hurdleMusic: play musica collisione con ostacolo senza ripetizione continua
*/
void SoundManager::hurdleMusic(void) { engine->play2D("sound/solid.wav", false); }