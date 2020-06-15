#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameWindow.h"
#include "Utente.h"

using namespace std;

#pragma once
static class MenuManager 
{
    static GLint width, height;

    static GLuint PlayButtonTexture,
        ShopButtonTexture,
        AudioTextureOn,
        AudioTextureOff,
        Background,
        TitleTexture;

    /* tasto GIOCA */
    static float play_larghezza;
    static float play_altezza;
    static float play_centro_x;
    static float play_centro_y;
    static float play_x1;
    static float play_x2;
    static float play_y1;
    static float play_y2;

    /* tasto disattiva Audio */
    static float sound_larghezza;
    static float sound_altezza;
    static float sound_x1;
    static float sound_x2;
    static float sound_y1;
    static float sound_y2;

    /* tasto opzioni */
    static float option_larghezza;
    static float option_altezza;
    static float option_x1;
    static float option_x2;
    static float option_y1;
    static float option_y2;

    /* bottoni per attivazione texture*/
    static float larghezza_bt_texture;
    static float altezza_bt_texture;
    static float bt_y1;
    static float bt_y2;

    /* Titolo */
    static float titleLarghezza;
    static float titleAltezza;
    static float Title_x1;
    static float Title_x2;
    static float Title_y1;
    static float Title_y2;

    static float bt1_x1;
    static float bt1_x2;
    static int prezzo_texture_1;
    
    static float bt2_x1;
    static float bt2_x2;
    static int prezzo_texture_2;

    static float bt3_x1;
    static float bt3_x2;
    static int prezzo_texture_3;

    static int window;  // finestra da chiudere 
    static int enable;
    static bool sound;

    static int acquistata;

    // Initialization routine.
    static void setup(void);

    // OpenGL window reshape routine.
    static void resize(int w, int h);

    static void loadExternalTextures(void);
    static void Rectangle(float x1, float y1, float x2, float y2);

    static void drawMenu(void);
    static void drawOption(void);
    static void mouseControl1(int button, int state, int x, int y);

    static void drawText(float x, float y, float z, int text, char message[]);
    static void drawText(float x, float y, float z, char message[]);

    static bool checkPlayButton(int x, int y);
    static bool checkSoundButton(int x, int y);
    static bool checkOptionButton(int x, int y);
    
    static bool checkButtonTexture_1(int x, int y);
    static bool checkButtonTexture_2(int x, int y);
    static bool checkButtonTexture_3(int x, int y);

public:
    static void start(void);

    

};

