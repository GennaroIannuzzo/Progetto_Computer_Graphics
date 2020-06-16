#include "Ball_Manager.h"

int Ball_Manager::eseguo = 0;

void Ball_Manager::incrementaVelocità(void)
{
    if (Platforms::getInstance()->getFallenPlatforms() > 2) 
    {
        Pallina::getInstance()->incrementSpeed();
        Platforms::getInstance()->setFallenPlatforms(0);
    }
}

void Ball_Manager::triggerObject(Piattaforma& p)
{
    int tipo = p.getTipo();     // Recupero il tipo di oggetto dalla piattaforma
    
    // Continua se l'oggetto è stato instanziato
    if (tipo <= 1) 
    {
        GLfloat bounding_box = (p.getOggetto()->getDim() / 2) + 1; // Bounding box per l'oggetto        
        GLfloat x_ball =  Pallina::getInstance()->getPosizione().getX();
        GLfloat z_ball =  Pallina::getInstance()->getPosizione().getZ();
        GLfloat x_obj = p.getOggetto()->getPosizione().getX();
        GLfloat z_obj = p.getOggetto()->getPosizione().getZ();
        
        x_obj += Platforms::getInstance()->getLastPoint().getX();
        z_obj += Platforms::getInstance()->getLastPoint().getZ();

        // Controlla se la pallina tocca il bounding_box dell'oggetto
        if (x_ball >= (x_obj - bounding_box) &&
            x_ball <= (x_obj + bounding_box) &&
            z_ball >= (z_obj - bounding_box) &&
            z_ball <= (z_obj + bounding_box))
        {
            // Scatta il trigger dell'oggetto
            p.getOggetto()->Trigger();
            p.dropOggetto();
        }

    }
}


void Ball_Manager::cadutaPallina(void)
{
    int flag = 0;

    GLfloat posx_Pallina =  Pallina::getInstance()->getPosizione().getX();
    GLfloat posz_Pallina =  Pallina::getInstance()->getPosizione().getZ();

    GLfloat x_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getX();
    GLfloat z_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getZ();

    Punto puntoApp = Platforms::getInstance()->getLastPoint() + Platforms::getInstance()->getPlatforms()[1].getPosizione();

    GLfloat x_Piattaforma_1 = puntoApp.getX();
    GLfloat z_Piattaforma_1 = puntoApp.getZ();

    GLfloat dimDiviso2 = Platforms::getInstance()->getPlatforms()[0].getDim() / 2;

    // Controllo Piattaforma 0
    if ((posx_Pallina) >= (x_Piattaforma_0 - dimDiviso2) &&
        (posx_Pallina) <= (x_Piattaforma_0 + dimDiviso2) &&
        (posz_Pallina) >= (z_Piattaforma_0 - dimDiviso2) &&
        (posz_Pallina) <= (z_Piattaforma_0 + dimDiviso2)) 
    {
        flag = 1;

        // Controlla Collisione oggetto
        triggerObject(Platforms::getInstance()->getPlatforms()[0]);
    
    }
    if (flag == 0)
    {
        if ((posx_Pallina) >= (x_Piattaforma_1 - dimDiviso2) &&
            (posx_Pallina) <= (x_Piattaforma_1 + dimDiviso2) &&
            (posz_Pallina) >= (z_Piattaforma_1 - dimDiviso2) &&
            (posz_Pallina) <= (z_Piattaforma_1 + dimDiviso2)) 
        {

            Platforms::getInstance()->triggerPlatform();
        }
        else 
        { 
            Utente::getInstance()->salvaFile();
            exit(69);
        }
    }

}

void Ball_Manager::initialMovement(void) 
{
    srand((unsigned)time(NULL));
    int scelta = rand() % 2;
    if (scelta == 0)
         Pallina::getInstance()->moveLeft();
    
    else if (scelta == 1)
         Pallina::getInstance()->moveRight();
    

    eseguo = 1;
}

void Ball_Manager::ballMovement(void) 
{
    if (eseguo == 0) 
        initialMovement();

    // Controlli Pallina
    cadutaPallina();

    incrementaVelocità();

    Pallina::getInstance()->moveBall();

}