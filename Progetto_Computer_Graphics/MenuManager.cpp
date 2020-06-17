#include "MenuManager.h"

/*  HANDLE: Riferimento astratto a una risorsa quando l'app fa riferimento a blocchi di memoria 
 *  o oggetti gestiti da un altro sistema come un DB o un SO.
 */
HANDLE MenuManager::hThread = 0;

/*  DWORD: Sta per Double Word, infatti indica un unsigned int che anziché essere a 16 bit è a 32 bit.
 *  ThreadID indica semplicemente l'ID del thread che viene creato.
 */
DWORD MenuManager::ThreadID = 0;

GLint MenuManager::width = 500;
GLint MenuManager::height = 500;

/* Textures Menu Principale */
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

/* Dimensioni Titolo */
float MenuManager::titleLarghezza = 340;
float MenuManager::titleAltezza = 100;
float MenuManager::Title_x1 = (width / 2) - (titleLarghezza / 2);
float MenuManager::Title_x2 = (width / 2) + (titleLarghezza / 2);
float MenuManager::Title_y2 = height - 10;
float MenuManager::Title_y1 = height - titleAltezza;

/* Dimensioni bottone per giocare */
float MenuManager::play_larghezza = 250;
float MenuManager::play_altezza = 60;
float MenuManager::play_centro_x = width / 2;
float MenuManager::play_centro_y = height / 2;
float MenuManager::play_x1 = play_centro_x - play_larghezza / 2;
float MenuManager::play_x2 = play_centro_x + play_larghezza / 2;
float MenuManager::play_y1 = (play_centro_y - play_altezza / 2) - 90;
float MenuManager::play_y2 = (play_centro_y + play_altezza / 2) - 90;

/* Dimensioni bottone per attivare e disattivare l'audio */
float MenuManager::sound_larghezza = 80;
float MenuManager::sound_altezza = 80;
float MenuManager::sound_x1 = width - sound_larghezza - 10;
float MenuManager::sound_x2 = width - 10;
float MenuManager::sound_y2 = 10 + sound_altezza;
float MenuManager::sound_y1 = 10;

/* Dimensione bottone per lo shop */
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

/* Disegna gli elementi della finestra principale */
void MenuManager::drawMenu(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Disegna il background
    glBindTexture(GL_TEXTURE_2D, Background);
    Rectangle(0.0, 0.0, 500, 500);
    
    // Disegna il titolo del gioco
    glBindTexture(GL_TEXTURE_2D, TitleTexture);
    Rectangle(Title_x1, Title_y1, Title_x2, Title_y2);

    // Disegna il bottone per iniziare a giocare
    glBindTexture(GL_TEXTURE_2D, PlayButtonTexture);
    Rectangle(play_x1, play_y1, play_x2, play_y2);

    // Disegna il bottone per andare nello shop
    glBindTexture(GL_TEXTURE_2D, ShopButtonTexture);
    Rectangle(option_x1, option_y1, option_x2, option_y2);

    // Disegna il bottone in base alla scelta di tenere o meno l'audio
    if(sound) glBindTexture(GL_TEXTURE_2D, AudioTextureOn);
    else glBindTexture(GL_TEXTURE_2D, AudioTextureOff);
    Rectangle(sound_x1, sound_y1, sound_x2, sound_y2);

    // Recupera il punteggio massimo e le monetine attuali
    int highScore = Utente::getInstance()->getPunteggioMassimo();
    int monete = Utente::getInstance()->getMonete();

    glColor3f(0.92, 0.92, 0.51);

    // Disegna l'high score e le monetine
    drawText(width / 2, height / 2 - 10, 0, highScore, (char*)"High Score:");
    drawText(width / 2, (height / 2) - 40, 0, monete, (char*)"Monete:");

    glutSwapBuffers();
}

/* Callback eseguita dal thread */
DWORD WINAPI MenuManager::ThreadFun(LPVOID lpParam)
{
    // Dormi per 1.5 secondi
    Sleep(1500);

    // Poni a 0 acquistata per cancellare la frase dallo schermo
    acquistata = 0;

    // Riponi il threadID a 0 per eseguire un nuovo thread
    ThreadID = 0;
    
    glutPostRedisplay();
    return 0;
}

/* Crea e manda in esecuzione un thread */
void MenuManager::executeThread(void)
{
    // Se il threadID è 0, allora crea il thread
    if (ThreadID == 0) {
        
        // Crea il thread senza passare parametri alla funzione 'ThreadFun'
        hThread = CreateThread(
            NULL,
            0,
            ThreadFun,
            NULL,
            0,
            &ThreadID
        );

        // Se hThread è NULL allora c'è stato un errore nella creazione del thread
        if (hThread == NULL)
            cout << "There was an error thread -> " << GetLastError() << endl;

        // Chiudi l'handle quando il thread termina l'esecuzione
        CloseHandle(hThread);
    }
}

/* Disegna la finestra per lo shop */
void MenuManager::drawOption(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Disegna un rettangolo attorno alla texture attiva
    if (Utente::getInstance()->textureAttiva() == 1) glRectf(bt1_x1 - 2, bt_y1 - 2, bt1_x2 + 2, bt_y2 + 2);
    if (Utente::getInstance()->textureAttiva() == 2) glRectf(bt2_x1 - 2, bt_y1 - 2, bt2_x2 + 2, bt_y2 + 2);
    if (Utente::getInstance()->textureAttiva() == 3) glRectf(bt3_x1 - 2, bt_y1 - 2, bt3_x2 + 2, bt_y2 + 2);

    // Disegna l'immagine della texture di base
    glBindTexture(GL_TEXTURE_2D, BaseTexture);
    Rectangle(bt1_x1, bt_y1, bt1_x2, bt_y2);

    // Disegna il bottone per tornare al menu principale
    glBindTexture(GL_TEXTURE_2D, back);
    Rectangle(option_x1, option_y1, option_x2, option_y2);

    // Recupera le monete attuali
    int monete = Utente::getInstance()->getMonete();

    // Disegna le monete attuali
    glColor3f(0.0, 0.0, 0.0);
    drawText(width / 2, height - 20, 0, monete, (char*)"Monete:");

    // Disegna il nome della texture di base
    drawText(bt1_x1 + larghezza_bt_texture/2, bt_y1 - 25, 0, (char*)"Pallina Base");

    // Disegna il nome della texture di basket
    drawText(bt2_x1 + larghezza_bt_texture / 2, bt_y1 - 25, 0, (char*)"Pallina Basket");
    if (!Utente::getInstance()->textureComprate(2) && Utente::getInstance()->textureAttiva() != 2)
    {
        // Disegna l'immagine della texture di basket bloccata
        glBindTexture(GL_TEXTURE_2D, BasketTexture_Blocked);
        drawText(bt2_x1 + larghezza_bt_texture / 2, bt_y1 - 50, 0, prezzo_texture_2, (char*)"Costo:");
    }
    // Disegna l'immagine della texture di basket
    else glBindTexture(GL_TEXTURE_2D, BasketTexture);

    Rectangle(bt2_x1, bt_y1, bt2_x2, bt_y2);

    // Disegna il nome della texture Mondo
    drawText(bt3_x1 + larghezza_bt_texture / 2, bt_y1 - 25, 0, (char*)"Pallina Mondo");
    if (!Utente::getInstance()->textureComprate(3) && Utente::getInstance()->textureAttiva() != 3)
    {
        // Disegna l'immagine della texture Mondo bloccata
        glBindTexture(GL_TEXTURE_2D, WorldTexture_Blocked);
        drawText(bt3_x1 + larghezza_bt_texture / 2, bt_y1 - 50, 0, prezzo_texture_3, (char*)"Costo:");
    }
    // Disegna l'immagine della texture Mondo
    else glBindTexture(GL_TEXTURE_2D, WorldTexture);

    Rectangle(bt3_x1, bt_y1, bt3_x2, bt_y2);

    // Disegna messaggio di avviso
    if (acquistata == 1)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Texture acquistata!");
    else if (acquistata == 2)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Spiacenti, texture troppo cara");
    else if (acquistata == 3)
        drawText(width / 2, height / 2 - 50, 0, (char*)"Texture impostata");
    
    // Esegui il thread nel caso sia stato scritto un messaggio di avviso
    if (acquistata != 0) executeThread();

    glutSwapBuffers();
}

/* Disegna un rettangolo con la corrispondenza dei vertici della texture */
void MenuManager::Rectangle(float x1, float y1, float x2, float y2)
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

/* Controlla il punto in cui tocca il mouse */
void MenuManager::mouseControl1(int button, int state, int x, int y)
{
    // Pulsante sinistro del mouse premuto
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        y = height - y;

        // Menu principale abilitato
        if (enable == 0)
        {
            // Verifica che prema il bottone di gioco
            if (checkPlayButton(x, y))
            {
                // Distruggi la finestra attuale
                glutDestroyWindow(window);

                // Gioca 
                GameWindow::start(sound);
            }
            // Verifica che prema il bottone dell'audio
            if (checkSoundButton(x, y))
            {
                sound = !sound;
                if (sound == true) cout << "volume ON" << endl;
                else cout << "volume OFF" << endl;
            }
            // Verifica che prema il bottone dello shop
            if (checkOptionButton(x, y))
            {
                // Abilita il disegno dell'altra finestra
                enable = 1;
                
                // Disegna l'altra finestra
                glutDisplayFunc(drawOption);
            }
        }
        // Shop Abilitato
        else if(enable == 1)
        {
            // Verifica che prema il bottone per attivare la prima texture
            if (checkButtonTexture_1(x, y))
            {
                // Verifica acquisto Texture 1
                if (!Utente::getInstance()->textureComprate(1) && Utente::getInstance()->textureAttiva() != 1)
                    (Utente::getInstance()->compraTexture(1)) ? acquistata = 1 : acquistata = 2;
            }

            // Verifica che prema il bottone per attivare la seconda texture
            if (checkButtonTexture_2(x, y))
            {
                // Verifica acquisto Texture 2
                if (!Utente::getInstance()->textureComprate(2) && Utente::getInstance()->textureAttiva() != 2)
                    (Utente::getInstance()->compraTexture(2)) ? acquistata = 1 : acquistata = 2;
            }

            // Verifica che prema il bottone per attivare la terza texture
            if (checkButtonTexture_3(x, y))
            {
                // Verifica acquisto Texture 3
                if (!Utente::getInstance()->textureComprate(3) && Utente::getInstance()->textureAttiva() != 3)
                    (Utente::getInstance()->compraTexture(3)) ? acquistata = 1 : acquistata = 2;
            }

            // Verifica che prema il bottone per tornare al menu principale
            if (checkOptionButton(x, y))
            {
                // Abilita la finestra principale
                enable = 0;

                // Disabilita i messaggi di avviso
                acquistata = 0;

                // Disegna la finestra principale
                glutDisplayFunc(drawMenu);
            }
        }
    }

    // Pulsante sinistro del mouse premuto
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && enable == 1)
    {
        y = height - y;

        // Verifica che prema il bottone per attivare la prima texture
        if (checkButtonTexture_1(x, y))
            if (Utente::getInstance()->textureComprate(1) && Utente::getInstance()->scegliTexture(1))
                acquistata = 3;

        // Verifica che prema il bottone per attivare la seconda texture
        if (checkButtonTexture_2(x, y))
            if (Utente::getInstance()->textureComprate(2) && Utente::getInstance()->scegliTexture(2))
                acquistata = 3;
        
        // Verifica che prema il bottone per attivare la terza texture
        if (checkButtonTexture_3(x, y))
            if (Utente::getInstance()->textureComprate(3) && Utente::getInstance()->scegliTexture(3))
                acquistata = 3;
    }
    
    glutPostRedisplay();
}

/* Disegna messaggio con intero */
void MenuManager::drawText(float x, float y, float z, int text, char message[])
{
    char sl[20];
    
    // Crea messaggio con testo e intero
    sprintf_s(sl, "%s %d", message, text);

    // Recupera lunghezza testo e centra il testo
    int widthString = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
    x -= widthString / 2;

    // Indica posizione di disegno
    glRasterPos3f(x, y, z);

    // Disegna il testo
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

/* Disegna messaggio senza intero */
void MenuManager::drawText(float x, float y, float z, char message[])
{
    char sl[200];

    // Crea messaggio
    sprintf_s(sl, "%s", message);
    
    // Recupera lunghezza testo e centra il testo
    int widthString = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
    x -= widthString / 2;

    // Indica posizione di disegno
    glRasterPos3f(x, y, z);

    // Disegna il testo
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

/* Carica le texture dalla cartella Textures */
void MenuManager::loadExternalTextures(void)
{
    /* Textures Menu Principale */

    // Background
    Background = SOIL_load_OGL_texture
    (
        "Textures/MenuTexture/ScreenGioco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Titolo
    TitleTexture = SOIL_load_OGL_texture
    (
        "Textures/MenuTexture/ZIGZAG.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Bottone di gioco
    PlayButtonTexture = SOIL_load_OGL_texture 
    (
        "Textures/MenuTexture/PlayGame.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    // Bottone Shop
    ShopButtonTexture = SOIL_load_OGL_texture 
    (
        "Textures/MenuTexture/Shop.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Attiva Audio
    AudioTextureOn = SOIL_load_OGL_texture(
        "Textures/MenuTexture/AudioOn.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Disattiva Audio
    AudioTextureOff = SOIL_load_OGL_texture(
        "Textures/MenuTexture/AudioOff.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    /* Shop Textures */

    // Immagine Texture di base
    BaseTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BlackTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Immagine Texture di basket
    BasketTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BasketTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Immagine Texture di basket bloccata
    BasketTexture_Blocked = SOIL_load_OGL_texture(
        "Textures/ShopTexture/BasketTexture_Blocked.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Immagine Texture Mondo
    WorldTexture = SOIL_load_OGL_texture(
        "Textures/ShopTexture/MondoTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Immagine Texture Mondo Bloccata
    WorldTexture_Blocked = SOIL_load_OGL_texture(
        "Textures/ShopTexture/MondoTexture_Blocked.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    // Bottone torna al menu principale
    back = SOIL_load_OGL_texture(
        "Textures/ShopTexture/back.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    // Imposta parametri per le texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

/* Routine di inizializzazione */
void MenuManager::setup(void)
{
    // Colora lo sfondo di bianco
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Carica le Texture
    loadExternalTextures();

    // Specificare il modo in cui i valori di trama si combinano con i valori di colore di superficie correnti
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Abilita le Texture OpenGL
    glEnable(GL_TEXTURE_2D);
}

/* Metodo di ridimensionamento di OpenGL */
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

/* Verifica bottone di gioco */
bool MenuManager::checkPlayButton(int x, int y)
{
    if (play_x1 < x && x < play_x2 && play_y1 < y && y < play_y2)
        return true;
    return false;
}

/* Verifica Bottone dell'audio */
bool MenuManager::checkSoundButton(int x, int y)
{
    if (sound_x1 < x && x < sound_x2 && sound_y1 < y && y < sound_y2)
        return true;
    return false;
}

/* Verifica bottone shop e torna indietro nel menu principale */
bool MenuManager::checkOptionButton(int x, int y)
{
    if (option_x1 < x && x < option_x2 && option_y1 < y && y < option_y2)
        return true;
    return false;
}

/* Verifica bottone Texture 1 */
bool MenuManager::checkButtonTexture_1(int x, int y)
{
    if (bt1_x1 < x && x < bt1_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}

/* Verifica bottone Texture 2 */
bool MenuManager::checkButtonTexture_2(int x, int y)
{
    if (bt2_x1 < x && x < bt2_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}

/* Verifica bottone Texture 3 */
bool MenuManager::checkButtonTexture_3(int x, int y)
{
    if (bt3_x1 < x && x < bt3_x2 && bt_y1 < y && y < bt_y2)
        return true;
    return false;
}

/* Metodo principale della finestra menu principale e shop */
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

