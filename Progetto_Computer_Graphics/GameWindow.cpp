#include "GameWindow.h"

int GameWindow::interval = 1000 / 60;
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

GLfloat GameWindow::spot_direction[] = { 0.0, -1.0, 0.0 };

// Metodo che permette di convertire da string a LPCWSTR (Formato particolare di Windows)
wstring GameWindow::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void GameWindow::initializeTextures(void)
{
    WIN32_FIND_DATA fd;
    HANDLE hFind;
    LPCWSTR wild_name;
    vector<wstring> names;
    PTSTR tempFileName;

    string dirpath = "Textures/Palla/*.*";

    wstring stemp = s2ws(dirpath.c_str());
    wild_name = stemp.c_str();

    hFind = FindFirstFile(wild_name, &fd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (FindNextFile(hFind, &fd));
        FindClose(hFind);
    }

    vector<string> vettore;

    for (auto it = names.begin(); it != names.end(); ++it)
    {
        string s((const char*)&(*it)[0], sizeof(wchar_t) / sizeof(char) * (*it).size());
        s.erase(std::remove(s.begin(), s.end(), '\0'), s.end());
        vettore.push_back(s);
    }

    string dirtexture = "Textures/Palla/";

    string pathnamefile;

    for (auto it = vettore.begin(); it != vettore.end(); ++it)
    {
        pathnamefile = dirtexture + *it;
        Pallina::getInstance()->getBallTextures().push_back(SOIL_load_OGL_texture(
            pathnamefile.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT));
    }

    Monete::setTextureMoneta();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void GameWindow::initializeDrawingObjects(void)
{
    // Oggetto Pallina
    gluQuadricDrawStyle(Pallina::getInstance()->getSphere(), GLU_FILL);
    gluQuadricTexture(Pallina::getInstance()->getSphere(), GL_TRUE);
    gluQuadricNormals(Pallina::getInstance()->getSphere(), GLU_SMOOTH);

    // Oggetto Moneta
    gluQuadricDrawStyle(Monete::getDisk(), GLU_FILL);
    gluQuadricTexture(Monete::getDisk(), GL_TRUE);
    gluQuadricNormals(Monete::getDisk(), GLU_SMOOTH);

}

// Initialization routine.
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

void GameWindow::drawLight(void)
{
    // Luce
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
    // glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
}                                           

// Drawing routine.
void GameWindow::drawScene(void)
{
    srand((unsigned)time(NULL));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_LIGHTING);

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

    glEnable(GL_LIGHTING);

    light1_position[0] = Pallina::getInstance()->getPosizione().getX();
    light1_position[1] = Pallina::getInstance()->getPosizione().gety() + 15;
    light1_position[2] = Pallina::getInstance()->getPosizione().getZ();

    glPushMatrix();
        drawLight();
    glPopMatrix();

    glPushMatrix();

    // TODO: Ruotare la monetina per vederla dritta
    moneta->drawObject(Pallina::getInstance()->getPosizione().getX() - 7,
        Pallina::getInstance()->getPosizione().gety(),
        Pallina::getInstance()->getPosizione().getZ() + 30);

    // glRotatef(45, 1.0, 0.0, 0.0);
    // glRotatef(45, 0.0, 0.0, 1.0);

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

void GameWindow::start(bool sound)
{
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Progetto.cpp");

    if(sound)
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