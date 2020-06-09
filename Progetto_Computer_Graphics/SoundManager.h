#pragma once
#include <irrKlang.h>

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class SoundManager
{
	static SoundManager* instance;
	
	ISoundEngine* engine;

	SoundManager();

public:
	static SoundManager* getInstance();

	void gameMusic(void);
	void hurdleMusic(void);
};

