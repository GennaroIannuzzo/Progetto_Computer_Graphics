//////////////////////////////////////////
// Progetto.cpp
//
// Progetto Esame Computer Graphics.
// 
//////////////////////////////////////////

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "MenuManager.h"

using namespace std;

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    MenuManager::start();

    glutMainLoop();
    
}