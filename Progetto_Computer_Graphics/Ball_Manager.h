#include "Pallina.h"
#include "Platforms.h"
#include <time.h>

#pragma once
class Ball_Manager
{
private:
	
	static Ball_Manager* instance;

	// Costruttori
	Ball_Manager();
	Ball_Manager(int difficolt�);

	Pallina ball;
	int eseguo;

public:

	// Getter
	static Ball_Manager* getInstance();
	Pallina& getBall(void);
	
	void incrementaVelocit�(void);
	void cadutaPallina(void);
	void initialMovement(void);
	void ballMovement(void);
	void triggerObject(Piattaforma& p);
};