#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Ball_Manager.h"

using namespace std;

#pragma once

/* Classe per la gestione dell'input da tastiera */
static class Keyboard_Manager
{
public:

    // Metodo per l'elaborazione dell'input da tastiera
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

    // metodo che gestisce l'input da tastiera per il gioco (frecce direzionali)
    static void keyboard() {

        // Vai a sinistra
        if (GetAsyncKeyState(VK_LEFT)) { Pallina::getInstance()->moveLeft(); }

        // Vai a destra
        if (GetAsyncKeyState(VK_RIGHT)) { Pallina::getInstance()->moveRight(); }

    }
};