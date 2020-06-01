#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Keyboard_Manager.h"

#pragma once
static class Window_Manager
{
private:

    static int interval;

public:

    // Initialization routine.
    static void setup(void);

    // OpenGL window reshape routine.
    static void resize(int w, int h);

    // Update routine for glutTimerFunc
    static void update(int value);

    // Getter
    static int& getInterval(void);
};