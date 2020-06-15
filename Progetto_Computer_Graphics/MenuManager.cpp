#include "MenuManager.h"

GLint MenuManager::width = 500;
GLint MenuManager::height = 500;

GLuint MenuManager::PlayButtonTexture = 0;
GLuint MenuManager::ShopButtonTexture = 0;
GLuint MenuManager::AudioTextureOn = 0;
GLuint MenuManager::AudioTextureOff = 0;
GLuint MenuManager::Background = 0;
GLuint MenuManager::TitleTexture = 0;

/* Shop Textures */
GLuint MenuManager::BaseTexture = 0;
GLuint MenuManager::BasketTexture = 0;
GLuint MenuManager::BasketTexture_Blocked = 0;
GLuint MenuManager::WorldTexture = 0;
GLuint MenuManager::WorldTexture_Blocked = 0;
GLuint MenuManager::back = 0;

float MenuManager::titleLarghezza = 340;
float MenuManager::titleAltezza = 100;
float MenuManager::Title_x1 = (width / 2) - (titleLarghezza / 2);
float MenuManager::Title_x2 = (width / 2) + (titleLarghezza / 2);
float MenuManager::Title_y2 = height - 10;
float MenuManager::Title_y1 = height - titleAltezza;

float MenuManager::play_larghezza = 250;
float MenuManager::play_altezza = 60;
float MenuManager::play_centro_x = width / 2;
float MenuManager::play_centro_y = height / 2;
float MenuManager::play_x1 = play_centro_x - play_larghezza / 2;
float MenuManager::play_x2 = play_centro_x + play_larghezza / 2;
float MenuManager::play_y1 = (play_centro_y - play_altezza / 2) - 90;
float MenuManager::play_y2 = (play_centro_y + play_altezza / 2) - 90;

float MenuManager::sound_larghezza = 80;
float MenuManager::sound_altezza = 80;
float MenuManager::sound_x1 = width - sound_larghezza - 10;
float MenuManager::sound_x2 = width - 10;
float MenuManager::sound_y2 = 10 + sound_altezza;
float MenuManager::sound_y1 = 10;

float MenuManager::option_larghezza = 120;
float MenuManager::option_altezza = 50;
float MenuManager::option_x1 = 10;
float MenuManager::option_x2 = 10 + option_larghezza;
float MenuManager::option_y2 = 10 + option_altezza;
float MenuManager::option_y1 = 10;

/* Bottoni Scelta texture */
float MenuManager::altezza_bt_texture = 150;
float MenuManager::larghezza_bt_texture = 150;

float MenuManager::bt_y1 = height - 200;
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

int MenuManager::acquistata = 0;

void MenuManager::drawMenu(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(0.0, 0.0, 0.0);

    // glColor3f(0.8, 0.8, 0.8); // No highlight.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // glRectf(play_x1, play_y1, play_x2, play_y2);

    // glRectf(sound_x1, sound_y1, sound_x2, sound_y2);

    // glRectf(option_x1, option_y1, option_x2, option_y2);

    glBindTexture(GL_TEXTURE_2D, Background);
    Rectangle(0.0, 0.0, 500, 500);
    
    glBindTexture(GL_TEXTURE_2D, TitleTexture);
    Rectangle(Title_x1, Title_y1, Title_x2, Title_y2);

    glBindTexture(GL_TEXTURE_2D, PlayButtonTexture);
    Rectangle(play_x1, play_y1, play_x2, play_y2);

    glBindTexture(GL_TEXTURE_2D, ShopButtonTexture);
    Rectangle(option_x1, option_y1, option_x2, option_y2);

    if(sound) glBindTexture(GL_TEXTURE_2D, AudioTextureOn);
    else glBindTexture(GL_TEXTURE_2D, AudioTextureOff);
    Rectangle(sound_x1, sound_y1, sound_x2, sound_y2);

    int highScore = Utente::getInstance()->getPunteggioMassimo();
    int monete = Utente::getInstance()->getMonete();

    glColor3f(0.92, 0.92, 0.51);

    drawText(width / 2, height / 2 - 10, 0, highScore, (char*)"High Score:");
    drawText(width / 2, (height / 2) - 40, 0, monete, (char*)"Monete:");

    glutSwapBuffers();
}

void MenuManager::drawOption(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(0.0, 0.0, 0.0);

    // glColor3f(0.8, 0.8, 0.8); // No highlight.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    if (Utente::getInstance()->textureAttiva() == 1) glRectf(bt1_x1 - 2, bt_y1 - 2, bt1_x2 + 2, bt_y2 + 2);
    if (Utente::getInstance()->textureAttiva() == 2) glRectf(bt2_x1 - 2, bt_y1 - 2, bt2_x2 + 2, bt_y2 + 2);
    if (Utente::getInstance()->textureAttiva() == 3) glRectf(bt3_x1 - 2, bt_y1 - 2, bt3_x2 + 2, bt_y2 + 2);

    glBindTexture(GL_TEXTURE_2D, BaseTexture);
    Rectangle(bt1_x1, bt_y1, bt1_x2, bt_y2);

    glBindTexture(GL_TEXTURE_2D, back);
    Rectangle(option_x1, option_y1, option_x2, option_y2);

    int monete = Utente::getInstance()->getMonete();

    glColor3f(0.0, 0.0, 0.0);
    drawText(width / 2, height - 20, 0, monete, (char*)"Monete:");

    drawText(bt1_x1 + larghezza_bt_texture/2, bt_y1 - 25, 0, (char*)"Pallina Base");

    drawText(bt2_x1 + larghezza_bt_texture / 2, bt_y1 - 25, 0, (char*)"Pallina Basket");
    if (!Utente::getInstance()->textureComprate(2) && Utente::getInstance()->textureAttiva() != 2)
    {
        glBindTexture(GL_TEXTURE_2D, BasketTexture_Blocked);
        drawText(bt2_x1 + larghezza_bt_texture / 2, bt_y1 - 50, 0, prezzo_texture_2, (char*)"Costo:");
    }
    else glBindTexture(GL_TEXTURE_2D, BasketTexture);

    Rectangle(bt2_x1, bt_y1, bt2_x2, bt_y2);

    drawText(bt3_x1 + larghezza_bt_texture / 2, bt_y1 - 25, 0, (char*)"Pallina Mondo");
    if (!Utente::getInstance()->textureComprate(3) && Utente::getInstance()->textureAttiva() != 3)
    {
        glBindTexture(GL_TEXTURE_2D, WorldTexture_Blocked);
        drawText(bt3_x1 + larghezza_bt_texture / 2, bt_y1 - 50, 0, prezzo_texture_3, (char*)"Costo:");
    }
    else glBindTexture(GL_TEXTURE_2D, WorldTexture);

    Rectangle(bt3_x1, bt_y1, bt3_x2, bt_y2);

    if (acquistata == 1)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Texture acquistata!");
    else if (acquistata == 2)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Spiacenti, texture troppo cara");
    else if(acquistata == 3)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Texture impostata");
 
    glutSwapBuffers();
}

void MenuManager::Rectangle(float x1, float y1, float x2, float y2)
/*specifies a side of a cube*/
{
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3d(x1, y2, 0.0);

        glTexCoord2f(0.0, 1.0);
        glVertex3d(x1, y1, 0.0);

        glTexCoord2f(1.0, 1.0);
        glVertex3d(x2, y1, 0.0);

        glTexCoord2f(1.0, 0.0);
        glVertex3d(x2, y2, 0.0);
    glEnd();
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
                        // drawText(width / 2 - 20, 200, 0, (char*)"Texture acquistata!");
                        acquistata = 1;
                    else
                        // drawText(width / 2 - 20, 200, 0, (char*)"Spiacenti, texture troppo cara");
                        acquistata = 2;
            }

            if (checkButtonTexture_2(x, y))
            {
                /*
                if (Utente::getInstance()->textureAttiva() == 2) cout << "la texture 2 è in uso" << endl;
                else if (Utente::getInstance()->textureComprate(2)) cout << "la texture 2 è già acquistata" << endl;
                else
                {
                    if (Utente::getInstance()->compraTexture(2))
                        cout << "texture 2 acquistata" << endl;
                    else
                        cout << "sei povero! la texture 2 non te la compri!" << endl;
                }
                */
                if (!Utente::getInstance()->textureComprate(2) && Utente::getInstance()->textureAttiva() != 2)
                    (Utente::getInstance()->compraTexture(2)) ? acquistata = 1 : acquistata = 2;
            }

            if (checkButtonTexture_3(x, y))
            {
                /*
                if (Utente::getInstance()->textureAttiva() == 3) cout << "la texture 3 è in uso" << endl;
                else if (Utente::getInstance()->textureComprate(3)) cout << "la texture 3 è già acquistata" << endl;
                else
                {
                    if (Utente::getInstance()->compraTexture(3))
                        cout << "texture 3 acquistata" << endl;
                    else
                        cout << "sei povero! la texture 3 non te la compri!" << endl;
                }
                */
                if (!Utente::getInstance()->textureComprate(3) && Utente::getInstance()->textureAttiva() != 3)
                    (Utente::getInstance()->compraTexture(3)) ? acquistata = 1 : acquistata = 2;
            }

            if (checkOptionButton(x, y))
            {
                cout << "tasto opzioni" << endl;
                enable = 0;
                acquistata = 0;
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
                // cout << " texture impostata come predefinita" << endl;
                acquistata = 3;
        }

        if (checkButtonTexture_2(x, y))
        {
            if (Utente::getInstance()->textureComprate(2) && Utente::getInstance()->scegliTexture(2))
                // cout << " texture impostata come predefinita" << endl;
                acquistata = 3;
        }

        if (checkButtonTexture_3(x, y))
        {
            if (Utente::getInstance()->textureComprate(3) && Utente::getInstance()->scegliTexture(3))
                // cout << " texture impostata come predefinita" << endl;
                acquistata = 3;
        }
    }
    
    glutPostRedisplay();
}

void MenuManager::drawText(float x, float y, float z, int text, char message[])
{
    

    char sl[20];
    sprintf_s(sl, " %s %d", message, text);

    int widthString = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
    x -= widthString / 2;

    glRasterPos3f(x, y, z);

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

void MenuManager::drawText(float x, float y, float z, char message[])
{
    char sl[200];
    sprintf_s(sl, " %s ", message);
    
    int widthString = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
    x -= widthString / 2;

    glRasterPos3f(x, y, z);

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

void MenuManager::loadExternalTextures(void)
{
    Background = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "Textures/MenuTexture/ScreenGioco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    TitleTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "Textures/MenuTexture/ZIGZAG.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    PlayButtonTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "Textures/MenuTexture/PlayGame.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    ShopButtonTexture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "Textures/MenuTexture/Shop.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    AudioTextureOn = SOIL_load_OGL_texture(
        "Textures/MenuTexture/AudioOn.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    AudioTextureOff = SOIL_load_OGL_texture(
        "Textures/MenuTexture/AudioOff.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    /* Shop Textures */

    BaseTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BlackTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    BasketTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BasketTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    BasketTexture_Blocked = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BasketTexture_Blocked.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    WorldTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/MondoTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    WorldTexture_Blocked = SOIL_load_OGL_texture(
        "Textures/ShopTexture/MondoTexture_Blocked.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    back = SOIL_load_OGL_texture(
        "Textures/ShopTexture/back.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void MenuManager::setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    loadExternalTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
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

    // cout << "bt altezza -> " << bt_y1 << endl;
}

