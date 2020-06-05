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
    glLoadIdentity();
    
    gluLookAt(Pallina::getInstance()->getPosizione().getX() - 15.0,
              Pallina::getInstance()->getPosizione().getY() + 20.0,
              Pallina::getInstance()->getPosizione().getZ() + 15.0,
              Pallina::getInstance()->getPosizione().getX(),
              0.0, 
              Pallina::getInstance()->getPosizione().getZ(),
              1.0, 0.0, -1.0);

    int punteggio = Utente::getInstance()->incrementaPunteggio();
    int monete = Utente::getInstance()->getMonete();


    Window_Manager::drawText(Pallina::getInstance()->getPosizione().getX() + 50,
                             Pallina::getInstance()->getPosizione().getY(),
                             Pallina::getInstance()->getPosizione().getZ() - 30,
                             punteggio);

    Window_Manager::drawText(Pallina::getInstance()->getPosizione().getX() - 10,
                             Pallina::getInstance()->getPosizione().getY(),
                             Pallina::getInstance()->getPosizione().getZ() + 30,
                             monete);
    
    glPushMatrix();
        Utente::getInstance()->drawMonete(Pallina::getInstance()->getPosizione().getX() - 7,
                                          Pallina::getInstance()->getPosizione().getY(),
                                          Pallina::getInstance()->getPosizione().getZ() + 30);
    glPopMatrix();
    
    glPushMatrix();
        Utente::getInstance()->drawVite(Pallina::getInstance()->getPosizione().getX() - 30,
                                        Pallina::getInstance()->getPosizione().getY(),
                                        Pallina::getInstance()->getPosizione().getZ() + 9);
    glPopMatrix();


    glPushMatrix();

        Platforms::getInstance()->drawPlatforms();

    glPopMatrix();
    
    Pallina::getInstance()->drawObject();

    glutSwapBuffers();
}


// Main routine.
int main(int argc, char** argv)
{
    Utente::getInstance()->setDifficolta(1);
    Pallina::getInstance()->setDifficolta(1);

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