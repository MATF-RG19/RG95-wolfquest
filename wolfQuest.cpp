
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "drawFunc.hpp"
#include "image.hpp"
using namespace std;

#define FILENAME0 "front.bmp"
#define FILENAME1 "back.bmp"

/* Identifikatori tekstura. */
static GLuint names[2];
// GLUT returns it in ASCII format
#define ESCAPE 27
#define SPACEBAR 32

#define TIMER_INTERVAL 20
#define TIMER_ID1 0
#define TIMER_ID2 1
#define TIMER_ID3 2
#define LEN 100
#define GODS_EYE 300
#define RAND_MATRIX_N 25
#define RAND_MATRIX_M 9
#define RAND_OBSTACLE 100

// kidam cpp, nista clase nista oop :(
struct CHRISTMASTREE{
  int randAngle;
  float randScale;
  float x;
  int z;
};

struct OBSTACLE{
  int type;
  int position;
  float x;
};
float avalancheMovement = 0;
float cameraMovement = 0;
int animationCamera = 1;
int animationAvalanche = 0;
int firstBaltoObstacle = 0;
int firstObstacle=0;
int firstTreeRow=0;
int shouldTurnRight = 0;
int shouldTurnLeft = 0;
float turning = 0;
bool baltoRIP=false;

vector<vector<CHRISTMASTREE>> randMatrix(RAND_MATRIX_N);
vector<OBSTACLE> randObstacle(RAND_OBSTACLE);

static int baltoPosition = 0;

static int windowWidth;
static int windowHeight;

float acceleration = 0;
float animationParameter = 0;
static float animationRunning = 0;
static float descending = 0;
float limbMovementCoef = 0;
float limbAccelation = 0;
float avalancheCameraMovement = 0;
float avalancheTextureMovement = 1;
// callback funkcije
static void onKeyboard(unsigned char key, int x, int y);
static void onSpecialKeyPress(int key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int id);

static void initialize(void);
static float matrix[16];
static void lightInitialization(void);
static void enableOpenglOptions(void);

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  // Postavljanje prozora
  // glutInitWindowSize(1200, 1200);
  glutInitWindowSize(800,800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Wolf Quest");

  //predpr inicijalizacija
  for ( int i = 0 ; i < RAND_MATRIX_N; i++ )
    randMatrix[i].resize(RAND_MATRIX_M);
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

void onReshape(int width, int height){
  windowWidth = width;
  windowHeight = height;

  // Viewport
  glViewport(0, 0, width, height);

  // Postavljanje projekcije
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float) width / height, 1, GODS_EYE);
}

void onKeyboard(unsigned char key, int x, int y){
  switch(key){
    case 'r':
      animationParameter = 0;
      animationRunning = 0;
      firstTreeRow = 0;
      firstObstacle = 0;
      firstBaltoObstacle = 0;
      baltoRIP = false;
      baltoPosition = 0;
      limbMovementCoef = 0;
      descending = 0;
      turning = 0;
      shouldTurnRight = 0;
      shouldTurnLeft = 0;
      randInitialization();
      glutPostRedisplay();
      break;
    case 's':
    case 'S':
      animationRunning = 0;
      break;
    case SPACEBAR: //BUG 3xSpace dok vrti 3x brze ide
      if(!animationRunning && animationCamera == 0){
        animationRunning = 1;
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
      }
      else if(animationCamera){
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
      }
      break;
    case ESCAPE:
      glDeleteTextures(2, names);
      exit(0);
      break;
  }
}
void onSpecialKeyPress(int key, int x, int y){

  switch(key){
    case GLUT_KEY_RIGHT:
      if(animationRunning){
        shouldTurnRight=1;
        shouldTurnLeft=0;
        if(baltoPosition != 1){
          baltoPosition += 1;
          glutPostRedisplay();
        }
        break;
      }
    case GLUT_KEY_LEFT:
      if(animationRunning){
        shouldTurnLeft=1;
        shouldTurnRight=0;
        if(baltoPosition != -1){
          baltoPosition += -1;
          glutPostRedisplay();
        }
        break;
      }
    }
}

void onTimer(int id){
    //TODO napraviti fino ubrzano, ne generise lepo nove jelke i prepreke
    if(id == TIMER_ID1){
      animationParameter++;
      acceleration+=0.002;
      limbAccelation+=0.004;
      if(limbAccelation>10){
        limbAccelation=10;
      }
      if(acceleration>4){
        acceleration=4;
      }
      if(animationRunning){
        for(int i=0;i<RAND_MATRIX_N;i++){
          for(int j=0;j<RAND_MATRIX_M;j++){
            randMatrix[i][j].x -= acceleration;
          }
        }
        if(randMatrix[firstTreeRow][0].x < -225){
          /*
          originalno ako je na -225 znaci da
          se otvorio prostor za sldeci red koji ce na 400 (const)

          ako ode ispod -225 treba pomeriti na 400 - ta razlika (ubrzano)

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
          for(int k=0;k<RAND_MATRIX_M;k++){
            randMatrix[firstTreeRow][k].x = 400;
          }
          firstTreeRow++;
          if(firstTreeRow == RAND_MATRIX_N){
            firstTreeRow = 0;
          }
        }
        for(int i=0;i<RAND_OBSTACLE;i++){
          randObstacle[i].x -= acceleration;
        }
        if(randObstacle[firstObstacle].x <-70){
          randObstacle[firstObstacle].x = 9930;
          firstObstacle++;
          if(firstObstacle == RAND_OBSTACLE){
            firstObstacle = 0;
          }
        }
        if(randObstacle[firstBaltoObstacle].x<-10){
          firstBaltoObstacle++;
          cout<<firstBaltoObstacle<<endl;
          if(firstBaltoObstacle==RAND_OBSTACLE){
            firstBaltoObstacle = 0;
          }
        }
        BaltoCrashed(firstBaltoObstacle);
        if(baltoRIP){
          animationRunning = 0;
          animationAvalanche = 1;
        }
        if(shouldTurnRight && baltoPosition==1){
          turning+=0.2;
          if(turning>=8){
            turning=8;
            shouldTurnRight=0;
          }
        }
        if(shouldTurnRight && baltoPosition==0){
          turning+=0.2;
          if(turning>=0){
            turning=0;
            shouldTurnRight=0;
          }
        }
        if(shouldTurnLeft && baltoPosition==-1){
          turning-=0.2;
          if(turning<=-8){
            turning=-8;
            shouldTurnLeft=0;
          }
        }
        if(shouldTurnLeft && baltoPosition==0){
          turning-=0.2;
          if(turning<=0){
            turning=0;
            shouldTurnLeft=0;
          }
        }
        if(limbMovementCoef > 30)
            descending = 1;
        if(limbMovementCoef < -30)
            descending = 0;
        if(!descending)
            limbMovementCoef+=limbAccelation;
        if(descending)
            limbMovementCoef-=limbAccelation;
      }

    }
    else if(id == TIMER_ID2){
      cameraMovement++;
      if(cameraMovement>566){
        countdown();
        animationCamera = 0;
        animationRunning = 1;
      }
    }
    else if(id == TIMER_ID3){
      avalancheMovement++;
      avalancheTextureMovement+=1.5;
      avalancheCameraMovement++;
      if(avalancheCameraMovement>60){
        avalancheCameraMovement=60;
      }
      if(avalancheTextureMovement>290){
        avalancheTextureMovement=290;
        animationAvalanche=0;
      }
    }
    glutPostRedisplay();
    if (animationRunning)
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID1);
    else if (animationCamera){
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID2);
    }
    else if (animationAvalanche){
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID3);
    }
}

void onDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

  // Postavljanje pogleda
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //ispred
  // gluLookAt(10,2,2,5,2,0,0,1,0);
  // iza

  if(animationRunning){
    gluLookAt(-15,13,0,30,3,0,0,1,0);
  }
  else if(animationCamera){
    gluLookAt(15*sin(3*cameraMovement/360),1.67+cameraMovement/50,11*cos(3*cameraMovement/360),4,cameraMovement/68,0,0,1,0);
  }
  else{
    gluLookAt(-15+avalancheCameraMovement,13,0,30-avalancheCameraMovement,3,0,0,1,0);
  }

  // gluLookAt(20,10,0,-30,3,0,0,1,0);
  // gluLookAt(-15,10,0,30,3,0,0,1,0);
  // u njusku
  // gluLookAt(20,2,0,5,3,0,0,1,0);
  // fino
  // gluLookAt(10*sin(animationParameter/360),7,10*cos(animationParameter/360),4,2,0,0,1,0);
  // gluLookAt(12*sin(animationParameter/360),10,12*cos(animationParameter/360),0,6,0,0,1,0);
  // gluLookAt(4,7,10,4,2,0,0,1,0);
  // gluLookAt(30,4,30,0,0,0,0,1,0);

  drawAxes(LEN);
  drawBalto(baltoPosition);
  drawTrack();
  drawTerrain();
  drawObstacles();

  /* Crtaju se vrata kuce. */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);

        glTexCoord2f(0, 0);
        glVertex3f(250, 0,-300 );

        glTexCoord2f(1, 0);
        glVertex3f(250,300,-300);

        glTexCoord2f(1, 1);
        glVertex3f(250, 300, 300);

        glTexCoord2f(0, 1);
        glVertex3f(250, 0, 300);
    glEnd();

    /* Crta se zid kuce. */
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
      glNormal3f(0, 0, -1);

      glTexCoord2f(0, 0);
      glVertex3f(-250+avalancheTextureMovement, 0-avalancheTextureMovement/5,-300 );

      glTexCoord2f(1, 0);
      glVertex3f(-250+avalancheTextureMovement,300-avalancheTextureMovement/5,-300);

      glTexCoord2f(1, 1);
      glVertex3f(-250+avalancheTextureMovement, 300-avalancheTextureMovement/5, 300);

      glTexCoord2f(0, 1);
      glVertex3f(-250+avalancheTextureMovement, 0-avalancheTextureMovement/5, 300);
    glEnd();

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

  glutSwapBuffers();
}

void lightInitialization(void){
  float lightPosition[] = { 5, 40, 0, 0};
  float lightAmbient[] = { 0.1, 0.1, 0.1, 0.1,1};
  float lightDiffuse[] = { 1, 1, 1, 1};
  float lightSpecular[] = { 0.9, 0.9, 0.9, 1};

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void enableOpenglOptions(void){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
}
static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

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
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

    /* Inicijalizujemo matricu rotacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}
