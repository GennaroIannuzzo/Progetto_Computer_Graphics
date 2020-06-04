#include "Window_Manager.h"

int Window_Manager::interval = 1000 / 60;

// Initialization routine.
void Window_Manager::setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

// OpenGL window reshape routine.
void Window_Manager::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / h, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Window_Manager::update(int value) {

    // input handling (Richiamare il ball_Manager per ottenere la pallina)
    Keyboard_Manager::keyboard(Ball_Manager::getInstance()->getBall());

    Ball_Manager::getInstance()->ballMovement();

    // Call update() again in 'interval' milliseconds
    glutTimerFunc(interval, update, 0);

    // Redisplay frame
    glutPostRedisplay();

}

void Window_Manager::drawText(float x, float y, float z, float text) {
    glColor3f(0.0, 0.0, 0.0); 
    glRasterPos3f(x, y, z);
    char sl[20];
    sprintf_s(sl, "%f", text);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)sl);
}

// Getter
int& Window_Manager::getInterval(void) { return interval; }