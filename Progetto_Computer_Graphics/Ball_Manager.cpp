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

void Ball_Manager::cadutaPallina(void)
{
    // cout << "Coordinate Pallina" << endl;
    // ball.getPosizione().printPoint();
    // cout << "Coordinate piattaforma 0" << endl;
    // p.getLastPoint().printPoint();
    int flag = 0;

    GLfloat posx_Pallina = ball.getPosizione().getX();
    GLfloat posz_Pallina = ball.getPosizione().getZ();

    GLfloat x_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getX();
    GLfloat z_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getZ();

    Punto puntoApp = Platforms::getInstance()->getLastPoint() + Platforms::getInstance()->getPlatforms()[1].getPosizione();

    // cout << "lastPoint -> " << endl;
    // p.getLastPoint().printPoint();
    // cout << "puntoApp -> " << endl;
    // puntoApp.printPoint();

    GLfloat x_Piattaforma_1 = puntoApp.getX();
    GLfloat z_Piattaforma_1 = puntoApp.getZ();

    GLfloat dimDiviso2 = Platforms::getInstance()->getPlatforms()[0].getDim() / 2;

    GLfloat bounding_Box = 0.0;

    // Controllo Piattaforma 0
    if ((posx_Pallina + bounding_Box) >= (x_Piattaforma_0 - dimDiviso2) &&
        (posx_Pallina + bounding_Box) <= (x_Piattaforma_0 + dimDiviso2) &&
        (posz_Pallina - bounding_Box) >= (z_Piattaforma_0 - dimDiviso2) &&
        (posz_Pallina - bounding_Box) <= (z_Piattaforma_0 + dimDiviso2)) {
        // cout << "Stai dentro" << endl;
        flag = 1;
    }
    if (flag == 0)
    {
        if ((posx_Pallina + bounding_Box) >= (x_Piattaforma_1 - dimDiviso2) &&
            (posx_Pallina + bounding_Box) <= (x_Piattaforma_1 + dimDiviso2) &&
            (posz_Pallina - bounding_Box) >= (z_Piattaforma_1 - dimDiviso2) &&
            (posz_Pallina - bounding_Box) <= (z_Piattaforma_1 + dimDiviso2)) {

            Platforms::getInstance()->triggerPlatform();
            //exit(2);
        }
        else {
            // cout << "Hai perso" << endl;
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