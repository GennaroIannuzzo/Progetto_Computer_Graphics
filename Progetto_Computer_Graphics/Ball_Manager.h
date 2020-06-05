#include "Pallina.h"
#include "Platforms.h"
#include "Utente.h"
#include <time.h>

#pragma once
class Ball_Manager
{
private:
	
	static int eseguo;
	
public:

	static void incrementaVelocità(void);
	static void cadutaPallina(void);
	static void initialMovement(void);
	static void ballMovement(void);
	static void triggerObject(Piattaforma& p);
};