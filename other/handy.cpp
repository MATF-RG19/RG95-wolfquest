#include "handy.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

/* biblioteka za muziku
  Hvalaヾ(⌐■_■)ノ♪ Borise
*/
#include "../irrKlangLib/include/irrKlang.h"

using namespace std;

// link sa irrKlag.dll
using namespace irrklang;
#pragma comment(lib, "irrKlangLib/lib");

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

extern bool baltoRIP;
extern float turning;
extern vector<vector<CHRISTMASTREE>> randMatrix;
extern vector<OBSTACLE> randObstacle;
extern ISound *music;
extern ISoundEngine *engine;

void BaltoCrashed(int firstBaltoObstacle) {

  switch (randObstacle[firstBaltoObstacle].type) {
  // STEEL
  case 0:
    if (randObstacle[firstBaltoObstacle].x < 11 &&
        randObstacle[firstBaltoObstacle].x > -5) {
      switch (randObstacle[firstBaltoObstacle].position) {
      case -1:
        if (turning < -5.0) {
          baltoRIP = true;
          // cout<<"STEEL LEFT"<<endl;
        }
        break;
      case 0:
        if (-3.0 < turning && turning < 3.0) {
          baltoRIP = true;
          // cout<<"STEEL MID"<<endl;
        }
        break;
      case 1:
        if (turning > 5.0) {
          baltoRIP = true;
          // cout<<"STEEL RIGHT"<<endl;
        }
        break;
      }
    }
    break;
    // TREE
  case 1:
    if (randObstacle[firstBaltoObstacle].x < 9 &&
        randObstacle[firstBaltoObstacle].x > -2) {
      switch (randObstacle[firstBaltoObstacle].position) {
      case -1:
        if (turning < -3.0) {
          baltoRIP = true;
          // cout<<"TREE LEFT"<<endl;
        }
        break;
      case 0:
        if (-5.0 < turning && turning < 5.0) {
          baltoRIP = true;
          // cout<<"TREE MID"<<endl;
        }
        break;
      case 1:
        if (turning > 3.0) {
          baltoRIP = true;
          // cout<<"TREE RIGHT"<<endl;
        }
        break;
      }
    }
    break;
  }
}

void randInitialization(void) {
  srand(time(NULL));
  int k, q;
  k = -200;
  q = 12;
  for (int i = 0; i < RAND_MATRIX_N; i++) {
    q = 12;
    for (int j = 0; j < RAND_MATRIX_M; j++) {
      randMatrix[i][j].randAngle = rand() % 31;
      randMatrix[i][j].randScale =
          ((float) rand()) / ((float) RAND_MAX) / 3.0 + 0.66;
      randMatrix[i][j].x = k;
      randMatrix[i][j].z = q;
      q += 15;
    }
    k += 25;
  }
  k = 30;
  for (int i = 0; i < RAND_OBSTACLE; i++) {
    randObstacle[i].x        = k;
    randObstacle[i].type     = rand() % 2;
    randObstacle[i].position = rand() % 3 - 1;
    k += 100;
  }
  // ne zelim a prva prepreka bude na sredini
  randObstacle[0].position = -1;

  randMatrix[8][0].randAngle = 0;
  randMatrix[8][0].randScale = 0.5;
}

void countdown(void) {
  glutPostRedisplay();
  usleep(1000000);
  usleep(500000);

  // ugasiti Borisa, pogledaj crtani
  if (music) {
    music->drop();
    engine->drop();
  }

  // zvuk kijanja, to pokrenulo lavinu
  // ozbiljno pogledaj crtani to mi omiljeni -> Balto(1995)!!!
  engine = createIrrKlangDevice(); // kreiranje zvuka
  if (!engine) {
    // hmmm ne bi ovo trebalo
    cout << "greska muzika" << endl;
  }
  music = engine->play3D("irrKlangLib/media/apcih.mp3", vec3df(0, 0, 0), true,
                         false, true);
  usleep(9000000);
  if (music) {
    music->drop();
    // cout<<"gotova ova muzika"<<endl;
    engine->drop();
  }
  // run.mp3
  engine = createIrrKlangDevice();
  if (!engine) {
    cout << "greska muzika" << endl;
  }
  music = engine->play3D("irrKlangLib/media/run.mp3", vec3df(0, 0, 0), true,
                         false, true);

  glutPostRedisplay();
}
