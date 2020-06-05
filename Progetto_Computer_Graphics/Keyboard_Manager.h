#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Ball_Manager.h"

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

    static void keyboard() {

        // Ball movement 
        if (GetAsyncKeyState(VK_LEFT)) {
             Pallina::getInstance()->moveLeft();
            // glutPostRedisplay();
        }

        if (GetAsyncKeyState(VK_RIGHT)) {
             Pallina::getInstance()->moveRight();
            // glutPostRedisplay();
        }

    }
};