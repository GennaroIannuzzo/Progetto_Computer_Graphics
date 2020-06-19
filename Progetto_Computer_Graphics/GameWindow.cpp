#include "GameWindow.h"

int GameWindow::interval = 1000 / 60;
int GameWindow::window = 0;

// Simbolo moneta in basso a destra
Monete* GameWindow::moneta = new Monete();

// Colore della luce (ponendo tutti i valori ad 1 si ottiene una luce bianca)
GLfloat GameWindow::light1_ambient[] = { 1, 1, 1, 1.0 };
GLfloat GameWindow::light1_diffuse[] = { 1.0, 1.0, 1.0, 1 };
GLfloat GameWindow::light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Posizione della luce
GLfloat GameWindow::light1_position[] = {
    Pallina::getInstance()->getPosizione().getX(),
    Pallina::getInstance()->getPosizione().gety() + 2,
    Pallina::getInstance()->getPosizione().getZ(),
    1.0
};

// L'asse secondo il quale la luce punta
GLfloat GameWindow::spot_direction[] = { 0.0, -1.0, 0.0 };

/* Inizializza le texture della pallina e della monetina */
void GameWindow::initializeTextures(void)
{
    // Stringa per indicare la texture da inizializzare
    string stringa;

    if (Utente::getInstance()->textureAttiva() == 1) stringa = "0_Black.png";
    if (Utente::getInstance()->textureAttiva() == 2) stringa = "1_Basket_Ball_Texture.png";
    if (Utente::getInstance()->textureAttiva() == 3) stringa = "2_World_Map_Texture.png";
    
    Pallina::getInstance()->setTexture(stringa);

    Monete::setTextureMoneta();

    // Imposta i parametri per le texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

/* Inizializza le quadriche da disegnare */
void GameWindow::initializeDrawingObjects(void)
{
    // Oggetto Pallina (Sfera)
    gluQuadricDrawStyle(Pallina::getInstance()->getSphere(), GLU_FILL);
    gluQuadricTexture(Pallina::getInstance()->getSphere(), GL_TRUE);
    gluQuadricNormals(Pallina::getInstance()->getSphere(), GLU_SMOOTH);

    // Oggetto Moneta (Disco)
    gluQuadricDrawStyle(Monete::getDisk(), GLU_FILL);
    gluQuadricTexture(Monete::getDisk(), GL_TRUE);
    gluQuadricNormals(Monete::getDisk(), GLU_SMOOTH);
}

/* Routine di inizializzazione */
void GameWindow::setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    
    initializeTextures();
    
    initializeDrawingObjects();
}

/* Metodo di ridimensionamento di OpenGL */
void GameWindow::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / h, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Callback per il metodo glutTimerFunc */
void GameWindow::update(int value)
{
    // Quando l'utente perde il gioco si ferma
    if (Utente::getInstance()->getGameOver() == 0)
    {
        Keyboard_Manager::keyboard();

        Ball_Manager::ballMovement();

        glutTimerFunc(interval, update, 0);

        glutPostRedisplay();
    }
    
}

/* Disegna un intero sullo schermo sotto forma di testo */
void GameWindow::drawText(float x, float y, float z, int text)
{
    // Specifica il colore del testo
    glColor3f(0.0, 0.0, 0.0);

    // Specifica la posizione del testo
    glRasterPos3f(x, y, z);

    char sl[20];
    sprintf_s(sl, "%d", text);

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

/* Recupera l'intervallo della frequenza di aggiornamento */
int& GameWindow::getInterval(void) { return interval; }

/* Specifica i parametri di disegno della luce nella scena */
void GameWindow::drawLight(void)
{
    // Colore della luce
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    
    // Posizione della luce
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    // Angolo della luce
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);

    // Specifica la distribuzione dell'intensità della luce
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);

    // Specifica il verso di illuminazione della luce
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
}                                           

/* Metodo per disegnare la scena */
void GameWindow::drawScene(void)
{
    srand((unsigned)time(NULL));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Disabilita la luce per dare il colore ai testi
    glDisable(GL_LIGHTING);

    // Carica la matrice d'identità nella pila di matrici di trasformazione
    glLoadIdentity();

    // Specifica la posizione della telecamera
    gluLookAt(Pallina::getInstance()->getPosizione().getX() - 15.0,
        Pallina::getInstance()->getPosizione().gety() + 20.0,
        Pallina::getInstance()->getPosizione().getZ() + 15.0,
        Pallina::getInstance()->getPosizione().getX(),
        0.0,
        Pallina::getInstance()->getPosizione().getZ(),
        1.0, 0.0, -1.0);

    // Recupera il punteggio e il quantitativo di monete attuale
    int punteggio = Utente::getInstance()->incrementaPunteggio();
    int monete = Utente::getInstance()->getMonete();
    
    // Disegna il punteggio e il numero di monete nella scena
    GameWindow::drawText(Pallina::getInstance()->getPosizione().getX() + 50,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() - 30,
        punteggio);

    GameWindow::drawText(Pallina::getInstance()->getPosizione().getX() - 10,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 30,
        monete);

    // Abilita la luce
    glEnable(GL_LIGHTING);

    // Posiziona la luce sopra la pallina da gioco
    light1_position[0] = Pallina::getInstance()->getPosizione().getX();
    light1_position[1] = Pallina::getInstance()->getPosizione().gety() + 15;
    light1_position[2] = Pallina::getInstance()->getPosizione().getZ();

    // Disegna le varie luci
    glPushMatrix();
        drawLight();
    glPopMatrix();

    glPushMatrix();

    // Disegna la monetina simbolo
    moneta->drawObject(Pallina::getInstance()->getPosizione().getX() - 7,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 30);

    glPopMatrix();

    glPushMatrix();

    // Disegna le vite a dispozione per l'utente
    Utente::getInstance()->drawVite(Pallina::getInstance()->getPosizione().getX() - 30,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 9);

    glPopMatrix();

    glPushMatrix();

    // Disegna le piattaforme
    Platforms::getInstance()->drawPlatforms();

    glPopMatrix();

    // Disegna la pallina
    Pallina::getInstance()->drawObject();

    glutSwapBuffers();

}

// Ottiene l'ID della finestra attuale
int GameWindow::getWindowId(void) { return window; }

void printInteraction(void)
{
    system("CLS");
    cout << "------------------------------ INTERAZIONE ------------------------------" << endl;
    cout << "Premi le frecce direzionali sinistra/destra per muovere la pallina" << endl << endl;
    cout << "Premi ESC per terminare l'applicazione" << endl;
    cout << "-------------------------------------------------------------------------" << endl << endl;
}

/* Metodo principale della finestra di gioco */
void GameWindow::start(bool sound)
{
    printInteraction();
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("Progetto.cpp");

    // Effettua un reset del gioco nel caso l'utente perda e voglia effettuare una nuova partita
    Utente::getInstance()->resetGame();

    // Abilita o disabilita il suono in base a sound
    if(sound)
        SoundManager::getInstance()->gameMusic();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glutTimerFunc(getInterval(), update, 0);
    glutKeyboardFunc(Keyboard_Manager::keyInput);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

}
