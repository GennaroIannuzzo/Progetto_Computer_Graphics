#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Keyboard_Manager.h"

#pragma once
static class Window_Manager
{
protected:

    static void setup(void);
    static void resize(int w, int h);
    static void update(int value);
    static void drawText(float x, float y, float z, int text);
    static void drawScene(void);
    
    // Getter
    static int& getInterval(void);

public:

    static void start(void);
};