#include "Ball_Manager.h"

Ball_Manager* Ball_Manager::instance = 0;

Ball_Manager* Ball_Manager::getInstance()
{
	if (instance == 0)
		instance = new Ball_Manager(1);

	return instance;
}

Ball_Manager::Ball_Manager() {}

Ball_Manager::Ball_Manager(int difficoltà)
{
    eseguo = 0;
	ball = Pallina(difficoltà);
}

// Getter
Pallina& Ball_Manager::getBall(void) { return ball; }

void Ball_Manager::incrementaVelocità(void)
{
    if (Platforms::getInstance()->getFallenPlatforms() > 2) {
        ball.incrementSpeed();
        Platforms::getInstance()->setFallenPlatforms(0);
    }
}

void Ball_Manager::triggerObject(Piattaforma& p)
{
    int tipo = p.getTipo();     // Recupero il tipo di oggetto dalla piattaforma
    
    // Continua se l'oggetto è stato instanziato
    if (tipo <= 1) {
        GLfloat bounding_box = p.getOggetto()->getDim() / 2; // Bounding box per l'oggetto        
        GLfloat x_ball = ball.getPosizione().getX();
        GLfloat z_ball = ball.getPosizione().getZ();
        GLfloat x_obj = p.getOggetto()->getPosizione().getX();
        GLfloat z_obj = p.getOggetto()->getPosizione().getZ();
        /*

        GLfloat dim_mezzi = p.getOggetto()->getDim() / 2;

        GLfloat posizione_x_min = -dim_mezzi + dimensione_oggetto;
        GLfloat posizione_x_max = dim_mezzi - dimensione_oggetto;

        GLfloat posizione_z_max = dim_mezzi - dimensione_oggetto;
        GLfloat posizione_z_min = -dim_mezzi + dimensione_oggetto;

        
            
        */

        cout << "Last_Point x-> " << Platforms::getInstance()->getLastPoint().getX() << endl;
        cout << "Last_Point z-> " << Platforms::getInstance()->getLastPoint().getZ() << endl;

        x_obj += Platforms::getInstance()->getLastPoint().getX();
        z_obj += Platforms::getInstance()->getLastPoint().getZ();

        // Controlla se la pallina tocca il bounding_box dell'oggetto
        if (x_ball >= (x_obj - bounding_box) &&
            x_ball <= (x_obj + bounding_box) &&
            z_ball >= (z_obj - bounding_box) &&
            z_ball <= (z_obj + bounding_box))
        {
            // Scatta il trigger dell'oggetto
            // p.getOggetto()->Trigger();
            exit(10);
        }
        else
        {
            cout << "Palla: ";
            ball.getPosizione().printPoint();
            cout << endl;

            cout << "Oggetto: x-> " << x_obj << " z -> " << z_obj;
            cout << endl;
        }
    }
}


void Ball_Manager::cadutaPallina(void)
{
    int flag = 0;

    GLfloat posx_Pallina = ball.getPosizione().getX();
    GLfloat posz_Pallina = ball.getPosizione().getZ();

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
        (posz_Pallina) <= (z_Piattaforma_0 + dimDiviso2)) {
        flag = 1;

        // Controlla Collisione oggetto
        triggerObject(Platforms::getInstance()->getPlatforms()[0]);
    
    }
    if (flag == 0)
    {
        if ((posx_Pallina) >= (x_Piattaforma_1 - dimDiviso2) &&
            (posx_Pallina) <= (x_Piattaforma_1 + dimDiviso2) &&
            (posz_Pallina) >= (z_Piattaforma_1 - dimDiviso2) &&
            (posz_Pallina) <= (z_Piattaforma_1 + dimDiviso2)) {

            Platforms::getInstance()->triggerPlatform();
        }
        else { 
            cout << "Sono fuori, il tuo punteggio -> " << ball.salvaPunteggio() << endl;
            exit(1);
        }
    }

}

void Ball_Manager::initialMovement(void) {

    srand((unsigned)time(NULL));
    int scelta = rand() % 2;
    if (scelta == 0) {
        ball.moveLeft();
    }
    else if (scelta == 1) {
        ball.moveRight();
    }

    // ball.moveLeft();

    eseguo = 1;
}

void Ball_Manager::ballMovement(void) {

    if (eseguo == 0) initialMovement();

    ball.moveBall();

    // glutPostRedisplay();
}