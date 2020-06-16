#include "Pallina.h"
#include "Platforms.h"
#include "Utente.h"
#include <time.h>

#pragma once
class Ball_Manager
{
private:
	
	static int eseguo;

	static void initialMovement(void); 
	static void incrementaVelocit�(void);
	static void cadutaPallina(void);
	static void triggerObject(Piattaforma& p);

public:

	static void ballMovement(void);
	
};