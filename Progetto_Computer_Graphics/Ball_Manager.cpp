#include "Ball_Manager.h"

int Ball_Manager::eseguo = 0; // Attributo per avere la direzione iniziale randomica una sola volta

/* Incrementa la velocità della pallina quando il numero di piattaforme supera una certa soglia. */
void Ball_Manager::incrementaVelocità(void)
{
    if (Platforms::getInstance()->getFallenPlatforms())
    {
        // Incrementa la velocità e azzera il contatore delle piattaforme cadute
        Pallina::getInstance()->incrementSpeed();
        Platforms::getInstance()->setFallenPlatforms(0);
    }
}

/* Attiva il Trigger dell'oggetto posto sulla piattaforma quando la pallina interseca il bounding box dell'oggetto. */
void Ball_Manager::triggerObject(Piattaforma& p)
{
    int tipo = p.getTipo(); // Recupero il tipo di oggetto dalla piattaforma
    
    // Continua se l'oggetto è stato instanziato e se si tratta di una monetina o un ostacolo
    if (tipo <= 1) 
    {
        // Bounding box per l'oggetto
        GLfloat bounding_box = (p.getOggetto()->getDim() / 2) + 1.5; 
        
        // Recupera la posizione della pallina e dell'oggetto
        GLfloat x_ball =  Pallina::getInstance()->getPosizione().getX();
        GLfloat z_ball =  Pallina::getInstance()->getPosizione().getZ();
        GLfloat x_obj = p.getOggetto()->getPosizione().getX();
        GLfloat z_obj = p.getOggetto()->getPosizione().getZ();
        
        // Aggiunge la posizione della piattaforma per avere la posizione effettiva dell'oggetto
        x_obj += Platforms::getInstance()->getLastPoint().getX();
        z_obj += Platforms::getInstance()->getLastPoint().getZ();

        // Controlla se la pallina tocca il bounding_box dell'oggetto
        if (x_ball >= (x_obj - bounding_box) &&
            x_ball <= (x_obj + bounding_box) &&
            z_ball >= (z_obj - bounding_box) &&
            z_ball <= (z_obj + bounding_box))
        {
            // Scatta il trigger dell'oggetto
            p.getOggetto()->Trigger();
            
            // Elimina l'oggetto quando scatta il trigger
            p.dropOggetto();
        }

    }
}

/* Controlla che la pallina si trovi ancora sulla piattaforma e non sia caduta. */
void Ball_Manager::cadutaPallina(void)
{
    int flag = 0;

    // Recupera la posizione attuale della pallina
    GLfloat posx_Pallina =  Pallina::getInstance()->getPosizione().getX();
    GLfloat posz_Pallina =  Pallina::getInstance()->getPosizione().getZ();

    // Recupera il centro della piattaforma sulla quale si trova la pallina
    GLfloat x_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getX();
    GLfloat z_Piattaforma_0 = Platforms::getInstance()->getLastPoint().getZ();

    // Recupera la piattaforma successiva
    Punto puntoApp = Platforms::getInstance()->getLastPoint() + Platforms::getInstance()->getPlatforms()[1].getPosizione();

    // Prendi il punto centrale della piattaforma successiva
    GLfloat x_Piattaforma_1 = puntoApp.getX();
    GLfloat z_Piattaforma_1 = puntoApp.getZ();

    // Dividi per due la dimensione della piattaforma per calcolare gli angoli
    GLfloat dimDiviso2 = Platforms::getInstance()->getPlatforms()[0].getDim() / 2;

    // Controlla se la pallina si trovi sulla piattaforma 0
    if ((posx_Pallina) >= (x_Piattaforma_0 - dimDiviso2) &&
        (posx_Pallina) <= (x_Piattaforma_0 + dimDiviso2) &&
        (posz_Pallina) >= (z_Piattaforma_0 - dimDiviso2) &&
        (posz_Pallina) <= (z_Piattaforma_0 + dimDiviso2)) 
    {
        flag = 1;

        // Controlla Collisione con eventuale oggetto
        triggerObject(Platforms::getInstance()->getPlatforms()[0]);
    
    }

    // Se la pallina non si trova sulla piattaforma 0, controlla che si trovi sulla piattaforma 1
    if (flag == 0)
    {
        if ((posx_Pallina) >= (x_Piattaforma_1 - dimDiviso2) &&
            (posx_Pallina) <= (x_Piattaforma_1 + dimDiviso2) &&
            (posz_Pallina) >= (z_Piattaforma_1 - dimDiviso2) &&
            (posz_Pallina) <= (z_Piattaforma_1 + dimDiviso2))
        {

            Platforms::getInstance()->triggerPlatform();
        }
        else
            Utente::getInstance()->GameOver();
        
    }

}

/* Fa in modo che inizialmente la direzione di movimento della pallina sia casuale. */
void Ball_Manager::initialMovement(void) 
{
    srand((unsigned)time(NULL));
    int scelta = rand() % 2;

    if (scelta == 0) Pallina::getInstance()->moveLeft();
    else if (scelta == 1) Pallina::getInstance()->moveRight();
    
    // Evita che ad ogni frame venga eseguito il metodo
    eseguo = 1;
}

/* Esegue i metodi che effettuano i controlli sulla pallina e che ne eseguono il movimento */
void Ball_Manager::ballMovement(void) 
{
    // Esegue il movimento casuale solamente quando eseguo è 0
    if (eseguo == 0) 
        initialMovement();

    // Controlli Pallina
    cadutaPallina();

    // Incrementa la velocità della pallina
    incrementaVelocità();

    // Muove la pallina
    Pallina::getInstance()->moveBall();
}