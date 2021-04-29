#include "drawings/drawFunc.hpp"
#include "other/handy.hpp"
#include "textures/image.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


// #include "irrKlangLib/include/irrKlang.h"

using namespace std;
// using namespace irrklang;

// link sa irrKlag.dll
// #pragma comment(lib, "irrKlangLib/lib");
// ISoundEngine *engine;
// ISound *music;

#define FILENAME0 "textures/front.bmp"
#define FILENAME1 "textures/back.bmp"

// identifikatori tekstura
static GLuint names[2];
#define ESCAPE   27
#define SPACEBAR 32

#define TIMER_INTERVAL 20
#define TIMER_ID1      0 // animacija kretanja
#define TIMER_ID2      1 // animacija kamere
#define TIMER_ID3      2 // animacija lavine
#define LEN            100 // koord sistem

#define GODS_EYE      300 // dokle pogled seze
#define RAND_MATRIX_N 25 //
#define RAND_MATRIX_M 9 // dimenzije matrice jelki
#define RAND_OBSTACLE 100 // broj prepreka

// prepreka
struct OBSTACLE {
  int type; // Steel/Christmas tree
  int position; // levo/sredina/desno -> -1/0/1
  float x; // udaljenost od koordinatnog pocetka po x
};

// jelka
struct CHRISTMASTREE {
  int randAngle; // nagib [0-30] levo/desno
  float randScale; // velicina [0.7-1]
  float x; // udaljenost od koordinatnog pocetka po x
  int z; // po z
};

int score             = 0;
static bool isPressed = false; // space da samo 1 pozove

float avalancheMovement = 0; // pomeranje lavine(teksture)
float cameraMovement    = 0; // pomeranje pocetne kamere

// animacije camera/kretanje/lavina
static float animationRunning = 0; // animacija kretanja
int animationCamera           = 1; // animacija pocetne kamere
int animationAvalanche        = 0; // animacija lavine

// "beskonacno" generisanje prepreka i sume
int firstBaltoObstacle = 0; // prva prepreka ispred Balta
int firstObstacle      = 0; // prva prepreka za "brisanj"
int firstTreeRow       = 0; // prvi niz jelki za "brisanje"

// skretanje <-/->
int shouldTurnRight      = 0;
int shouldTurnLeft       = 0;
float turning            = 0; // polozaj Balta na traci
static int baltoPosition = 0; // levo/sredina/desno -> -1/0/1

bool baltoRIP = false;

vector<vector<CHRISTMASTREE>> randMatrix(RAND_MATRIX_N); // "suma jelki"
vector<OBSTACLE> randObstacle(RAND_OBSTACLE); // prepreke

// velicina prozora
static int windowWidth;
static int windowHeight;

// ubrzanja
float animationParameter = 0;
float acceleration       = 0; // ubrzanje prepreka i sume

// pomeranje nogu
static float descending = 0; // noge napred/nazad
float limbMovementCoef  = 0;
float limbAccelation    = 0;

// pomeranje kamere i teksture pri sudaru
float avalancheCameraMovement  = 0;
float avalancheTextureMovement = 1;

// callback funkcije
static void onKeyboard(unsigned char key, int x, int y);
static void onSpecialKeyPress(int key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int id);

static float matrix[16];
// inicijlizacija teksture
static void initialize(void);

// postavljanje svetla
static void lightInitialization(void);

// ukljucivanje dodatnih opcija
static void enableOpenglOptions(void);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  // Postavljanje prozora
  glutInitWindowSize(1100, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Wolf Quest");
  glutFullScreen();
  // kreiranje zvuka
  // engine = createIrrKlangDevice();
  // if (!engine) {
    // cout << "meh" << endl;
  // }

  // inicijalizacija tekstura, sume i prepreka
  for (int i = 0; i < RAND_MATRIX_N; i++) {
    randMatrix[i].resize(RAND_MATRIX_M);
  }
  initialize();
  randInitialization();

  // Registrovanje callback funkcija
  glutKeyboardFunc(onKeyboard);
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);
  glutSpecialFunc(onSpecialKeyPress);

  // uklnjucivanje dodatnih opengl opcija
  enableOpenglOptions();

  // crna pozadina
  glClearColor(0, 0, 0, 0);
  glutMainLoop();

  return 0;
}

void onReshape(int width, int height) {
  windowWidth  = width;
  windowHeight = height;

  // Viewport
  glViewport(0, 0, width, height);

  // Postavljanje projekcije
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float) width / height, 1, GODS_EYE);
}

void onKeyboard(unsigned char key, int x, int y) {
  switch (key) {
  // RESET
  /*
  **********************************************************

  ┬──┬ ノ( ゜-゜ノ)
  Reset stop i score

  ? 2 put kliknem reset a terminal
  a on ce meni Segmentation fault (╯°□°）╯︵ ┻━┻
  Ne znam kako prisupa nekoj nedozvoljenoj lokaciji
  Previse sam tuko glavom oko ovog, dosta vala
  Ako cete igrati vise od jednom
  lakse vama da ponovo pokrenete

  ? Sto se tice stop-a, velike online igrice
  nemaju pause dugme pa u tom duhu da obrisem i ja
  (Da mi je jednostavno uradio bih, ali kad se stopira
  npr dok ide prva animacija on umesto da krene
  stoji a muzika pici dalje, to samo jedan od mnogih
  situacija koje korisnik moze da proba i zaista nmg da sve
  slucajeve prolazim)

  ? Scor cu ispisvati u terminal jer
  u prethodnim verzijama sam ubacivao u countdown funkciji
  ispis jednostavnog teksta gde je namera bila odbrojavati
  3,2,1 GO... i krece Balto da trci, ali nikakav tekst
  ja video nisam.

  **********************************************************
  case 'r':
  case 'R':
    // ovo mi izgelda ne treba ali ene, za svaki slucaj
    avalancheMovement = 0;

    cameraMovement = 0;

    // noge
    descending = 0;
    limbMovementCoef = 0;
    limbAccelation = 0;

    // parametri camere i teksture
    avalancheCameraMovement = 0;
    avalancheTextureMovement = 1;

    animationParameter = 0;
    acceleration = 0;

    // animacije
    animationRunning = 0;
    animationCamera = 1;
    animationAvalanche =0;

    firstTreeRow = 0;
    firstObstacle = 0;
    firstBaltoObstacle = 0;
    baltoRIP = false;

    // skretanje
    turning = 0;
    shouldTurnRight = 0;
    shouldTurnLeft = 0;
    baltoPosition = 0;

    if (music){
      music->drop();
      engine->drop();
    }

    isPressed = false;
    randInitialization();
    glutPostRedisplay();
    break;

  // STOP
  case 's':
  case 'S':
    animationRunning = 0;
    break;
  */
  // START
  case SPACEBAR:
    if (!isPressed) {
      isPressed = true;
      // music     = engine->play3D("irrKlangLib/media/maybe.mp3", vec3df(0, 0, 0),
                            //  true, false, true);
      if (!animationRunning && animationCamera == 0) {
        animationRunning = 1;
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
      } else if (animationCamera) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
      }
    }

    break;
  // LIGHTS OUT
  case ESCAPE:
    glDeleteTextures(2, names);
    // if (music) {
      // music->drop();
      // engine->drop();
    // }

    exit(0);
    break;
  }
}
void onSpecialKeyPress(int key, int x, int y) {
  // pomeranje levo/desno
  switch (key) {
  case GLUT_KEY_RIGHT:
    if (animationRunning) {
      shouldTurnRight = 1;
      shouldTurnLeft  = 0;
      // ako vec ne ide ka poziciji 1(skroz desno) a kliknuto dugme
      if (baltoPosition != 1) {
        baltoPosition += 1;
        glutPostRedisplay();
      }
      break;
    }
  case GLUT_KEY_LEFT:
    if (animationRunning) {
      shouldTurnLeft  = 1;
      shouldTurnRight = 0;
      if (baltoPosition != -1) {
        baltoPosition += -1;
        glutPostRedisplay();
      }
      break;
    }
  }
}

void onTimer(int id) {

  // animacija trcanja
  if (id == TIMER_ID1) {
    animationParameter++;
    acceleration += 0.001;
    limbAccelation += 0.004;
    score++;
    if (score == 4710) {
      // if (music) {
        // music->drop();
        // engine->drop();
      // }
      cout << "Congratulations, you have successfully brought\n";
      cout << "cure to Nome, we are forever grateful\n";
      cout << "Hell we might even build you a statue in NY" << endl;
      exit(0);
    }
    // fiksirano ubrzanje nogu
    if (limbAccelation > 10) {
      limbAccelation = 10;
    }

    // fiksirano ubrzanje sume i prepreka
    if (acceleration > 4) {
      acceleration = 4;
    }
    if (animationRunning) {

      // translacija sume
      for (int i = 0; i < RAND_MATRIX_N; i++) {
        for (int j = 0; j < RAND_MATRIX_M; j++) {
          randMatrix[i][j].x -= acceleration;
        }
      }
      // ako prvi red jelki predje odredjenu granicu
      // iscrtava se na mesto poslednjeg reda(pre transl)
      if (randMatrix[firstTreeRow][0].x < -225) {
        /*
        originalno ako je na -225 znaci da
        se otvorio prostor za sldeci red koji ce na 400 (const)

        posto je ubrzano retanje skoro nikad nece biti tacno
        -225 nego manje pa bi precizno bilo 400 - ta razlika
        ali suma od 2*25*9 jelki posle svakog kruga je mnogo

        *400 TAKE IT OR LEAVE IT*
        ────────────────────██████──────────
        ──────────────────██▓▓▓▓▓▓██────────
        ────────────────██▓▓▓▓▒▒▒▒██────────
        ────────────────██▓▓▒▒▒▒▒▒██────────
        ──────────────██▓▓▓▓▒▒▒▒██──────────
        ──────────────██▓▓▒▒▒▒▒▒██──────────
        ────────────██▓▓▓▓▒▒▒▒▒▒██──────────
        ────────────████▒▒████▒▒██──────────
        ────────────██▓▓▒▒▒▒▒▒▒▒██──────────
        ──────────██────▒▒────▒▒██──────────
        ──────────████──▒▒██──▒▒██──────────
        ──────────██────▒▒────▒▒██──────────
        ──────────██▒▒▒▒▒▒▒▒▒▒▒▒██──────────
        ──────────████████████▒▒▒▒██────────
        ────────██▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██──────
        ──────██▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒██────
        ────██▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒██──
        ──██▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒██
        ██▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒██
        ██▓▓▒▒▓▓▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒██
        ██▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓██
        ──████▐▌▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐▌▐▌████──
        ────██▐▌▐▌▌▌▌▌▌▌▌▌▐▌▐▌▐▌▐▌▌▌▐▌██────
        ────██▌▌▐▌▐▌▌▌▐▌▌▌▌▌▐▌▌▌▌▌▌▌▌▌██────
        ──────██▌▌▐▌▐▌▐▌▐▌▐▌▐▌▐▌▌▌▌▌██──────
        ──────██▐▌▐▌▐▌████████▐▌▌▌▌▌██──────
        ────────██▒▒██────────██▒▒██────────
        ────────██████────────██████────────
        */

        for (int k = 0; k < RAND_MATRIX_M; k++) {
          randMatrix[firstTreeRow][k].x = 400;
        }
        firstTreeRow++;
        // kruzna lista
        if (firstTreeRow == RAND_MATRIX_N) {
          firstTreeRow = 0;
        }
      }

      // translacija prepreka
      for (int i = 0; i < RAND_OBSTACLE; i++) {
        randObstacle[i].x -= acceleration;
      }
      // ista stvar kao i sa jelkama
      if (randObstacle[firstObstacle].x < -70) {
        randObstacle[firstObstacle].x = 9930;
        firstObstacle++;
        if (firstObstacle == RAND_OBSTACLE) {
          firstObstacle = 0;
        }
      }

      // ako je Balto prosao prepreku
      // azurira se nova i gleda se kolizija sa njom
      if (randObstacle[firstBaltoObstacle].x < -10) {
        firstBaltoObstacle++;
        // cout<<firstBaltoObstacle<<endl;
        if (firstBaltoObstacle == RAND_OBSTACLE) {
          firstBaltoObstacle = 0;
        }
      }

      // kolizija
      BaltoCrashed(firstBaltoObstacle);
      if (baltoRIP) {
        animationRunning   = 0;
        animationAvalanche = 1;
      }

      // pomeranje levo/desno
      if (shouldTurnRight && baltoPosition == 1) {
        turning += 0.2;
        if (turning >= 8) {
          turning         = 8;
          shouldTurnRight = 0;
        }
      }
      if (shouldTurnRight && baltoPosition == 0) {
        turning += 0.2;
        if (turning >= 0) {
          turning         = 0;
          shouldTurnRight = 0;
        }
      }
      if (shouldTurnLeft && baltoPosition == -1) {
        turning -= 0.2;
        if (turning <= -8) {
          turning        = -8;
          shouldTurnLeft = 0;
        }
      }
      if (shouldTurnLeft && baltoPosition == 0) {
        turning -= 0.2;
        if (turning <= 0) {
          turning        = 0;
          shouldTurnLeft = 0;
        }
      }

      // parametri rotacije nogu, nikad ne predju 30*
      // Hvala (~˘▾˘)~ Ogi
      if (limbMovementCoef > 30)
        descending = 1;
      if (limbMovementCoef < -30)
        descending = 0;
      if (!descending)
        limbMovementCoef += limbAccelation;
      if (descending)
        limbMovementCoef -= limbAccelation;
    }

  }

  // animacija pocetne kamere
  else if (id == TIMER_ID2 && isPressed) {
    cameraMovement++;
    if (cameraMovement > 566) {
      countdown();
      animationCamera  = 0;
      animationRunning = 1;
    }
  }

  // animacija lavine
  else if (id == TIMER_ID3) {
    avalancheMovement++;
    avalancheTextureMovement += 1.5;
    avalancheCameraMovement++;
    if (avalancheCameraMovement > 60) {
      avalancheCameraMovement = 60;
    }
    // ako je lavina prekrila teren gasi "run" muziku
    if (avalancheTextureMovement > 290) {
      avalancheTextureMovement = 290;
      animationAvalanche       = 0;
      // if (music) {
        // music->drop();
        // engine->drop();
      // }
      cout << "Your score: ";
      cout << score;
      cout << "\nDont give up now, you got this!" << endl;
      exit(0);
    }
  }

  glutPostRedisplay();
  if (animationRunning)
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
  else if (animationCamera) {
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
  } else if (animationAvalanche) {
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID3);
  }
}

void onDisplay(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

  // Postavljanje pogleda
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (animationRunning) {
    gluLookAt(-15, 13, 0, 30, 3, 0, 0, 1, 0);
  } else if (animationCamera) {
    gluLookAt(15 * sin(3 * cameraMovement / 360), 1 + cameraMovement / 50,
              9 * cos(3 * cameraMovement / 360), 4, 0.5 + cameraMovement / 68,
              0, 0, 1, 0);
  } else {
    gluLookAt(-15 + avalancheCameraMovement, 13, 0,
              30 - avalancheCameraMovement, 3, 0, 0, 1, 0);
  }

  // drawAxes(LEN);
  drawBalto(baltoPosition);
  drawTrack();
  drawTerrain();
  drawObstacles();

  // tektura front (Nome/aurora)
  glBindTexture(GL_TEXTURE_2D, names[0]);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);

  glTexCoord2f(0, 0);
  glVertex3f(250, 0, -300);

  glTexCoord2f(1, 0);
  glVertex3f(250, 300, -300);

  glTexCoord2f(1, 1);
  glVertex3f(250, 300, 300);

  glTexCoord2f(0, 1);
  glVertex3f(250, 0, 300);
  glEnd();

  // tekstura back (lavina)
  glBindTexture(GL_TEXTURE_2D, names[1]);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);

  glTexCoord2f(0, 0);
  glVertex3f(-250 + avalancheTextureMovement, 0 - avalancheTextureMovement / 5,
             -300);

  glTexCoord2f(1, 0);
  glVertex3f(-250 + avalancheTextureMovement,
             300 - avalancheTextureMovement / 5, -300);

  glTexCoord2f(1, 1);
  glVertex3f(-250 + avalancheTextureMovement,
             300 - avalancheTextureMovement / 5, 300);

  glTexCoord2f(0, 1);
  glVertex3f(-250 + avalancheTextureMovement, 0 - avalancheTextureMovement / 5,
             300);
  glEnd();

  // iskljucivanje teksture
  glBindTexture(GL_TEXTURE_2D, 0);

  glutSwapBuffers();
}

void lightInitialization(void) {
  float lightPosition[] = {5, 40, 0, 0};
  float lightAmbient[]  = {0.1, 0.1, 0.1, 0.1, 1};
  float lightDiffuse[]  = {1, 1, 1, 1};
  float lightSpecular[] = {0.9, 0.9, 0.9, 1};

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void enableOpenglOptions(void) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
}
static void initialize(void) {
  // objekat koji predstavlja teskturu ucitanu iz fajla
  Image *image;

  // postavlja se boja pozadine
  glClearColor(0, 0, 0, 0);

  // ukljucuje se testiranje z-koordinate piksela
  glEnable(GL_DEPTH_TEST);

  // ukljucuju se teksture
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  /*
   * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
   * fajla.
   */
  image = image_init(0, 0);

  /* Kreira se prva tekstura. */
  image_read(image, FILENAME0);

  /* Generisu se identifikatori tekstura. */
  glGenTextures(2, names);

  glBindTexture(GL_TEXTURE_2D, names[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Kreira se druga tekstura. */
  image_read(image, FILENAME1);

  glBindTexture(GL_TEXTURE_2D, names[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Iskljucujemo aktivnu teksturu */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Unistava se objekat za citanje tekstura iz fajla. */
  image_done(image);

  /* Inicijalizujemo matricu rotacije. */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}
