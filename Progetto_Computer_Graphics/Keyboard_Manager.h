#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Pallina.h"

using namespace std;

#pragma once
static class Keyboard_Manager
{
public:

    // Keyboard input processing routine.
    static void keyInput(unsigned char key, int x, int y)
    {
        switch (key)
        {
        case 27:
            exit(0);
            break;
        default:
            break;
        }
    }

    static void keyboard(Pallina ball) {

        // Ball movement 
        if (GetAsyncKeyState(VK_LEFT)) {
            ball.moveLeft();
            glutPostRedisplay();
        }

        if (GetAsyncKeyState(VK_RIGHT)) {
            ball.moveRight();
            glutPostRedisplay();
        }

    }
};