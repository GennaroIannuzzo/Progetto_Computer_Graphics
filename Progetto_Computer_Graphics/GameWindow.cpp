#include "GameWindow.h"

int GameWindow::interval = 1000 / 60;
Monete* GameWindow::moneta = new Monete();

// Initialization routine.
void GameWindow::setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

// OpenGL window reshape routine.
void GameWindow::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / h, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GameWindow::update(int value)
{

    Keyboard_Manager::keyboard();

    Ball_Manager::ballMovement();

    glutTimerFunc(interval, update, 0);

    glutPostRedisplay();

}

void GameWindow::drawText(float x, float y, float z, int text)
{
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(x, y, z);
    char sl[20];
    sprintf_s(sl, "%d", text);

    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)sl);
}

// Getter
int& GameWindow::getInterval(void) { return interval; }

// Drawing routine.
void GameWindow::drawScene(void)
{
    srand((unsigned)time(NULL));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(Pallina::getInstance()->getPosizione().getX() - 15.0,
        Pallina::getInstance()->getPosizione().gety() + 20.0,
        Pallina::getInstance()->getPosizione().getZ() + 15.0,
        Pallina::getInstance()->getPosizione().getX(),
        0.0,
        Pallina::getInstance()->getPosizione().getZ(),
        1.0, 0.0, -1.0);

    int punteggio = Utente::getInstance()->incrementaPunteggio();
    int monete = Utente::getInstance()->getMonete();


    GameWindow::drawText(Pallina::getInstance()->getPosizione().getX() + 50,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() - 30,
        punteggio);

    GameWindow::drawText(Pallina::getInstance()->getPosizione().getX() - 10,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 30,
        monete);

    glPushMatrix();

    moneta->drawObject(Pallina::getInstance()->getPosizione().getX() - 7,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 30);

    glPopMatrix();

    glPushMatrix();

    Utente::getInstance()->drawVite(Pallina::getInstance()->getPosizione().getX() - 30,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 9);

    glPopMatrix();

    glPushMatrix();

    Platforms::getInstance()->drawPlatforms();

    glPopMatrix();

    Pallina::getInstance()->drawObject();

    glutSwapBuffers();

}

void GameWindow::start(void)
{
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Progetto.cpp");

    SoundManager::getInstance()->gameMusic();

    Utente::getInstance()->setDifficolta(1);
    Pallina::getInstance()->setDifficolta(1);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glutTimerFunc(getInterval(), update, 0);
    glutKeyboardFunc(Keyboard_Manager::keyInput);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

}