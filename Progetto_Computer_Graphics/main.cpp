///////////////////////////////////
// Progetto.cpp
//
// Progetto Esame Computer Graphics.
// 
///////////////////////////////////

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include "Platforms.h"
#include "Pallina.h"
#include "Keyboard_Manager.h"
#include "Window_Manager.h"

using namespace std;

int eseguo = 0;
Platforms p = Platforms();
Pallina ball = Pallina(1);

void incrementaVelocità(void)
{
    if (p.getFallenPlatforms() > 2) {
        ball.incrementSpeed();
        p.setFallenPlatforms(0);
    }
}

void cadutaPallina(void)
{
    // cout << "Coordinate Pallina" << endl;
    // ball.getPosizione().printPoint();
    // cout << "Coordinate piattaforma 0" << endl;
    // p.getLastPoint().printPoint();
    int flag = 0;

    GLfloat posx_Pallina = ball.getPosizione().getX();
    GLfloat posz_Pallina = ball.getPosizione().getZ();

    GLfloat x_Piattaforma_0 = p.getLastPoint().getX();
    GLfloat z_Piattaforma_0 = p.getLastPoint().getZ();
    
    Punto puntoApp = p.getLastPoint() + p.getPlatforms()[1].getPunto();

    // cout << "lastPoint -> " << endl;
    // p.getLastPoint().printPoint();
    // cout << "puntoApp -> " << endl;
    // puntoApp.printPoint();

    GLfloat x_Piattaforma_1 = puntoApp.getX();
    GLfloat z_Piattaforma_1 = puntoApp.getZ();

    GLfloat dimDiviso2 = p.getPlatforms()[0].getDim()/2;
    
    GLfloat bounding_Box = 0.0;

    // Controllo Piattaforma 0
    if ((posx_Pallina + bounding_Box) >= (x_Piattaforma_0 - dimDiviso2) &&
        (posx_Pallina + bounding_Box) <= (x_Piattaforma_0 + dimDiviso2) &&
        (posz_Pallina - bounding_Box) >= (z_Piattaforma_0 - dimDiviso2) &&
        (posz_Pallina - bounding_Box) <= (z_Piattaforma_0 + dimDiviso2)) {
        cout << "Stai dentro" << endl;
        flag = 1;
    }
    else {
        cout << "Stai fuori" << endl;
    }
    if (flag == 0)
    {
        if ((posx_Pallina + bounding_Box) >= (x_Piattaforma_1 - dimDiviso2) &&
            (posx_Pallina + bounding_Box) <= (x_Piattaforma_1 + dimDiviso2) &&
            (posz_Pallina - bounding_Box) >= (z_Piattaforma_1 - dimDiviso2) &&
            (posz_Pallina - bounding_Box) <= (z_Piattaforma_1 + dimDiviso2)) {

            p.triggerPlatform();
            //exit(2);
        }
        else {
            cout << "Hai perso" << endl;
            exit(1);
        }
    }

}

void initialMovement() {

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

void ballMovement() {

    // if (eseguo == 0) initialMovement();

    ball.moveBall();

    glutPostRedisplay();
}

// Drawing routine.
void drawScene(void)
{
    srand((unsigned)time(NULL));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3f(255.0, 0.0, 0.0);
    glLoadIdentity();

    // gluLookAt(0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0);

    gluLookAt(ball.getPosizione().getX() - 15, ball.getPosizione().getY() + 20, ball.getPosizione().getZ() + 15, ball.getPosizione().getX(), 0.0, ball.getPosizione().getZ(), 1.0, 0.0, -1.0);
    
    glPushMatrix();

        p.drawPlatforms();

    glPopMatrix();
    
    // glColor3f(0.0, 0.0, 255.0);
    // glTranslatef(0.0, 20.0, 0.0);
    // glutSolidSphere(2, (int)2* 6, (int)2 * 6);

    ballMovement();

    ball.drawPallina();

    // Controlli Pallina
    cadutaPallina();

    // incrementaVelocità();

    glutSwapBuffers();
}


// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Progetto.cpp");
    
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Window_Manager::resize);
    
    glutTimerFunc(Window_Manager::getInterval(), Window_Manager::update, 0);
    glutKeyboardFunc(Keyboard_Manager::keyInput);
    glewExperimental = GL_TRUE;
    glewInit();

    Window_Manager::setup();

    glutMainLoop();
}