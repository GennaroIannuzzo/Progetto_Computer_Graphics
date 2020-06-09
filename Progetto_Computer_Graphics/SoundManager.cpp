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

void SoundManager::gameMusic(void) { engine->play2D("sound/getout6db.wav", true); }

void SoundManager::hurdleMusic(void) { engine->play2D("sound/solid.wav", false); }