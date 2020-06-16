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
void SoundManager::gameMusic(void) { engine->play2D("sound/bipwave.wav", true); }

/*
	hurdleMusic: play musica collisione con ostacolo senza ripetizione continua
*/
void SoundManager::hurdleMusic(void) { engine->play2D("sound/solid.wav", false); }

/*
	coinMusic: play musica collisione con moneta senza ripetizione continua
*/
void SoundManager::coinMusic(void) { engine->play2D("sound/coin.wav", false); }

void SoundManager::resetMusic(void) 
{
	engine->drop(); 
	delete instance;
	instance = NULL;
	
}
