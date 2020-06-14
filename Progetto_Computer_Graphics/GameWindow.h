#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Window_Manager.h"
#include "Keyboard_Manager.h"
#include "Monete.h"
#include "soil.h"

#pragma once
static class GameWindow : public Window_Manager
{
private:

    static int interval;
    static int window;  // finestra da chiudere 

    // Colore della luce (ponendo tutti i valori ad 1 si ottiene una luce bianca)
    static GLfloat light1_ambient[];
    static GLfloat light1_diffuse[];
    static GLfloat light1_specular[];

    // Posizione della luce
    static GLfloat light1_position[];
    static GLfloat spot_direction[];

    static Monete* moneta;

    static void drawLight(void);

    // Initialization routine.
    static void setup(void);

    // OpenGL window reshape routine.
    static void resize(int w, int h);

    // Update routine for glutTimerFunc
    static void update(int value);

    // Update score
    static void drawText(float x, float y, float z, int text);

    static wstring s2ws(const string& s);

    // Initializes the textures for the ball and coins
    static void initializeTextures(void);

    // Initialize the objects to be drawn
    static void initializeDrawingObjects(void);

    // Getter
    static int& getInterval(void);

    static void drawScene(void);

public:
    
    static void start(bool sound);
};