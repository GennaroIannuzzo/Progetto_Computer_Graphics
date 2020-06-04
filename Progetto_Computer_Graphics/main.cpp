//////////////////////////////////////////
// Progetto.cpp
//
// Progetto Esame Computer Graphics.
// 
//////////////////////////////////////////

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include "Keyboard_Manager.h"
#include "Window_Manager.h"
#include "Platforms.h"
#include "Pallina.h"
#include "Ball_Manager.h"
#include "Utente.h"

using namespace std;

// Drawing routine.
void drawScene(void)
{
    srand((unsigned)time(NULL));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3f(255.0, 0.0, 0.0);
    glLoadIdentity();

    gluLookAt(Ball_Manager::getInstance()->getBall().getPosizione().getX() - 15.0,
        Ball_Manager::getInstance()->getBall().getPosizione().getY() + 20.0,
        Ball_Manager::getInstance()->getBall().getPosizione().getZ() + 15.0,
        Ball_Manager::getInstance()->getBall().getPosizione().getX(),
        0.0, 
        Ball_Manager::getInstance()->getBall().getPosizione().getZ(),
        1.0, 0.0, -1.0);

    float punteggio = Utente::getInstance()->incrementaPunteggio();

    Window_Manager::drawText(Ball_Manager::getInstance()->getBall().getPosizione().getX() + 50,
        Ball_Manager::getInstance()->getBall().getPosizione().getY(),
        Ball_Manager::getInstance()->getBall().getPosizione().getZ() - 30,
        punteggio);

    glPushMatrix();

        Platforms::getInstance()->drawPlatforms();

    glPopMatrix();
    
    // glColor3f(0.0, 0.0, 255.0);
    // glTranslatef(0.0, 20.0, 0.0);
    // glutSolidSphere(2, (int)2* 6, (int)2 * 6);

    // Ball_Manager::getInstance()->ballMovement();

    Ball_Manager::getInstance()->getBall().drawObject();

    // Controlli Pallina
    Ball_Manager::getInstance()->cadutaPallina();

    Ball_Manager::getInstance()->incrementaVelocità();

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