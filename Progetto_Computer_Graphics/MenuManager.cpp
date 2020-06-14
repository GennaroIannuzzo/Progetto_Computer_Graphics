#include "MenuManager.h"

GLint MenuManager::width = 500;
GLint MenuManager::height = 500;

float MenuManager::play_larghezza = 100;
float MenuManager::play_altezza = 30;
float MenuManager::play_centro_x = width / 2;
float MenuManager::play_centro_y = height / 2;
float MenuManager::play_x1 = play_centro_x - play_larghezza / 2;
float MenuManager::play_x2 = play_centro_x + play_larghezza / 2;
float MenuManager::play_y1 = play_centro_y - play_altezza / 2;
float MenuManager::play_y2 = play_centro_y + play_altezza / 2;

float MenuManager::sound_larghezza = 50;
float MenuManager::sound_altezza = 30;
float MenuManager::sound_x1 = width - sound_larghezza - 10;
float MenuManager::sound_x2 = sound_x1 + sound_larghezza;
float MenuManager::sound_y1 = height - (height - sound_altezza);
float MenuManager::sound_y2 = sound_y1 + sound_altezza;

float MenuManager::option_larghezza = 50;
float MenuManager::option_altezza = 30;
float MenuManager::option_x1 = width - option_larghezza - 10;
float MenuManager::option_x2 = sound_x1 + option_larghezza;
float MenuManager::option_y1 = height - option_altezza * 2;
float MenuManager::option_y2 = height - option_altezza;

float MenuManager::altezza_bt_texture = 60;
float MenuManager::larghezza_bt_texture = 150;

float MenuManager::bt_y1 = height - altezza_bt_texture * 3;
float MenuManager::bt_y2 = bt_y1 + altezza_bt_texture;

float MenuManager::bt1_x1 = (width / 3 - larghezza_bt_texture)/1.5;
float MenuManager::bt1_x2 = bt1_x1 + larghezza_bt_texture;

float MenuManager::bt2_x1 = bt1_x2 + bt1_x1;
float MenuManager::bt2_x2 = bt2_x1 + larghezza_bt_texture;

float MenuManager::bt3_x1 = bt2_x2 + bt1_x1;
float MenuManager::bt3_x2 = bt3_x1 + larghezza_bt_texture;

int MenuManager::window = 0;
int MenuManager::enable = 0;
bool MenuManager::sound = true;

int MenuManager::prezzo_texture_1 = 10;
int MenuManager::prezzo_texture_2 = 20;
int MenuManager::prezzo_texture_3 = 30;

void MenuManager::drawMenu(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glRectf(play_x1, play_y1, play_x2, play_y2);

    glRectf(sound_x1, sound_y1, sound_x2, sound_y2);

    glRectf(option_x1, option_y1, option_x2, option_y2);

    int highScore = Utente::getInstance()->getPunteggioMassimo();
    int monete = Utente::getInstance()->getMonete();
    
    drawText(width / 2, height - 40, 0, highScore, (char*)"High Score");
    drawText(width / 2, height - 80, 0, monete, (char*)"Monete");

    glutSwapBuffers();
}

void MenuManager::drawOption(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glRectf(bt1_x1, bt_y1, bt1_x2, bt_y2);

    glRectf(bt2_x1, bt_y1, bt2_x2, bt_y2);
    
    glRectf(bt3_x1, bt_y1, bt3_x2, bt_y2);
    
    glRectf(option_x1, option_y1, option_x2, option_y2);

    int monete = Utente::getInstance()->getMonete();

    drawText(width / 2, height - 80, 0, monete, (char*)"Monete");

    drawText(bt1_x1, bt_y1 - 25, 0, (char*)"Pallina di fuoco");
    if (!Utente::getInstance()->textureComprate(1) && Utente::getInstance()->textureAttiva() != 1)
        drawText(bt1_x1, bt_y1 - 60, 0, prezzo_texture_1, (char*)"Costo:");

    drawText(bt2_x1, bt_y1 - 25, 0, (char*)"Pallina di figa");
    if (!Utente::getInstance()->textureComprate(2) && Utente::getInstance()->textureAttiva()!=2)
        drawText(bt2_x1, bt_y1 - 60, 0, prezzo_texture_2, (char*)"Costo:");

    drawText(bt3_x1, bt_y1 - 25, 0, (char*)"Pallina di pussy");
    if (!Utente::getInstance()->textureComprate(3) && Utente::getInstance()->textureAttiva() != 3)
        drawText(bt3_x1, bt_y1 - 60, 0, prezzo_texture_3, (char*)"Costo:");
 
    glutSwapBuffers();
}

void MenuManager::mouseControl1(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        y = height - y;

        if (enable == 0)
        {
            if (checkPlayButton(x, y))
            {
                cout << "tasto gioca" << endl;

                glutDestroyWindow(window);

                GameWindow::start(sound);

            }
            if (checkSoundButton(x, y))
            {
                sound = !sound;
                if (sound == true)
                    cout << "volume ON " << endl;
                else
                    cout << "volume OFF " << endl;
            }
            if (checkOptionButton(x, y))
            {
                cout << "tasto opzioni" << endl;
                enable = 1;
                glutDisplayFunc(drawOption);

            }
        }
        else if(enable == 1)
        {
            if (checkButtonTexture_1(x, y))
            {
                /*
                if (Utente::getInstance()->textureAttiva() == 1) cout << "la texture 1 è in uso" << endl;
                else if(Utente::getInstance()->textureComprate(1)) cout << "la texture 1 è già acquistata" << endl;
                else
                {
                    if(Utente::getInstance()->compraTexture(1))
                        cout << "texture 1 acquistata" << endl;
                    else
                        cout << "sei povero! la texture 1 non te la compri!" << endl;
                }
                */
                if (!Utente::getInstance()->textureComprate(1) && Utente::getInstance()->textureAttiva() != 1)
                    if (Utente::getInstance()->compraTexture(1))
                        drawText(width / 2 - 20, height / 2, 0, (char*)"Texture acquistata!");
                    else
                        drawText(width / 2 - 20, height/2, 0, (char*)"Spiacenti, texture troppo cara");

            }

            if (checkButtonTexture_2(x, y))
            {
                if (Utente::getInstance()->textureAttiva() == 2) cout << "la texture 2 è in uso" << endl;
                else if (Utente::getInstance()->textureComprate(2)) cout << "la texture 2 è già acquistata" << endl;
                else
                {
                    if (Utente::getInstance()->compraTexture(2))
                        cout << "texture 2 acquistata" << endl;
                    else
                        cout << "sei povero! la texture 2 non te la compri!" << endl;
                }
            }

            if (checkButtonTexture_3(x, y))
            {
                if (Utente::getInstance()->textureAttiva() == 3) cout << "la texture 3 è in uso" << endl;
                else if (Utente::getInstance()->textureComprate(3)) cout << "la texture 3 è già acquistata" << endl;
                else
                {
                    if (Utente::getInstance()->compraTexture(3))
                        cout << "texture 3 acquistata" << endl;
                    else
                        cout << "sei povero! la texture 3 non te la compri!" << endl;
                }
            }

            if (checkOptionButton(x, y))
            {
                cout << "tasto opzioni" << endl;
                enable = 0;
                glutDisplayFunc(drawMenu);

            }
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && enable == 1)
    {
        y = height - y;

        if (checkButtonTexture_1(x, y))
        {
            if (Utente::getInstance()->textureComprate(1) && Utente::getInstance()->scegliTexture(1))
                cout << " texture impostata come predefinita" << endl;
        }

        if (checkButtonTexture_2(x, y))
        {
            if (Utente::getInstance()->textureComprate(2) && Utente::getInstance()->scegliTexture(2))
                cout << " texture impostata come predefinita" << endl;
        }

        if (checkButtonTexture_3(x, y))
        {
            if (Utente::getInstance()->textureComprate(3) && Utente::getInstance()->scegliTexture(3))
                cout << " texture impostata come predefinita" << endl;
        }
    }
    
    glutPostRedisplay();
}

void MenuManager::drawText(float x, float y, float z, int text, char message[])
{
    glColor3f(0.0, 0.0, 0.0);

    glRasterPos3f(x, y, z);
    char sl[20];
    sprintf_s(sl, " %s %d", message, text);

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

void MenuManager::drawText(float x, float y, float z, char message[])
{
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(x, y, z);
    char sl[200];
    sprintf_s(sl, " %s ", message);
    cout << message << endl;

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

void MenuManager::setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

}

void MenuManager::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool MenuManager::checkPlayButton(int x, int y)
{
    if (play_x1 < x && x < play_x2 && play_y1 < y && y < play_y2)
        return true;
    return false;
}

bool MenuManager::checkSoundButton(int x, int y)
{
    if (sound_x1 < x && x < sound_x2 && sound_y1 < y && y < sound_y2)
        return true;
    return false;
}

bool MenuManager::checkOptionButton(int x, int y)
{
    if (option_x1 < x && x < option_x2 && option_y1 < y && y < option_y2)
        return true;
    return false;
}

bool MenuManager::checkButtonTexture_1(int x, int y)
{
    if (bt1_x1 < x && x < bt1_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}

bool MenuManager::checkButtonTexture_2(int x, int y)
{
    if (bt2_x1 < x && x < bt2_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}

bool MenuManager::checkButtonTexture_3(int x, int y)
{
    if (bt3_x1 < x && x < bt3_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}


void MenuManager::start(void)
{
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    window = glutCreateWindow("Progetto.cpp");

    glutDisplayFunc(drawMenu);
    glutReshapeFunc(resize);

    glutMouseFunc(mouseControl1);

    setup();

}

