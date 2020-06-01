#include "Window_Manager.h"

int Window_Manager::interval = 1000 / 30;

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
    Keyboard_Manager::keyboard();

    // Call update() again in 'interval' milliseconds
    glutTimerFunc(interval, update, 0);

    // Redisplay frame
    glutPostRedisplay();

}

// Getter
int& Window_Manager::getInterval(void) { return interval; }