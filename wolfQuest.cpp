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

using namespace std;

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define LEN 100
#define GODS_EYE 300
#define RAND_MATRIX_N 50
#define RAND_MATRIX_M 10

// kidam cpp, nista clase nista oop :(
struct ALLRANDOM{
  int randAngle;
  float randScale;
};

// int koeficijent=1;
int shouldTurnRight = 0;
int shouldTurnLeft = 0;
float turning = 0;
vector<vector<ALLRANDOM>> randMatrix(RAND_MATRIX_N);

static int baltoPosition = 0;

static int windowWidth;
static int windowHeight;

float animationParameter = 0;
static float animationOngoing = 0;
static float descending = 0;
float limbMovementCoef = 0;

// callback funkcije
static void onKeyboard(unsigned char key, int x, int y);
static void onSpecialKeyPress(int key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int id);


static void lightInitialization(void);
static void enableOpenglOptions(void);

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  // Postavljanje prozora
  glutInitWindowSize(1200, 1200);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Wolf Quest");

  //predpr inicijalizacija
  for ( int i = 0 ; i < RAND_MATRIX_N; i++ )
    randMatrix[i].resize(RAND_MATRIX_M);
  srand(time(NULL));
  int i,j;
  for(i=0;i<RAND_MATRIX_N;i++){
    for(j=0;j<RAND_MATRIX_M;j++){
      randMatrix[i][j].randAngle=rand() % 31;
      randMatrix[i][j].randScale=((float)rand()) / ((float)RAND_MAX) / 3.0 + 0.66;
    }
  }
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
      animationOngoing = 0;
      limbMovementCoef = 0;
      descending = 0;
      turning = 0;
      glutPostRedisplay();
      break;
    case 's':
    case 'S':
      animationOngoing = 0;
      break;
    case 'g':
    case 'G':
      if(!animationOngoing){
        animationOngoing = 1;
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
      }
      break;
    case 27:
      exit(0);
      break;
  }
}
void onSpecialKeyPress(int key, int x, int y){

  switch(key){
    case GLUT_KEY_RIGHT:
      if(animationOngoing){
        shouldTurnRight=1;
        shouldTurnLeft=0;
        if(baltoPosition != 1){
          baltoPosition += 1;
          glutPostRedisplay();
        }
        break;
      }
    case GLUT_KEY_LEFT:
      if(animationOngoing){
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
    if(id == TIMER_ID){
      animationParameter++;
      // ASISTENT 
        // vector<ALLRANDOM> newTreeRow;
        // newTreeRow.resize(RAND_MATRIX_N);
        // for(int j=0;j<10;j++){
          // newTreeRow[j].randAngle=rand() % 31;
          // newTreeRow[j].randScale=((float)rand()) / ((float)RAND_MAX) / 3.0 + 0.66;
        // }
        // randMatrix.erase(randMatrix.begin()+1);
        // randMatrix.push_back(newTreeRow);
      // }
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
      if(limbMovementCoef == 30)
          descending = 1;
      if(limbMovementCoef == -30)
          descending = 0;
      if(!descending)
          limbMovementCoef++;
      if(descending)
          limbMovementCoef--;
    }
    glutPostRedisplay();
    if (animationOngoing)
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID);
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
  gluLookAt(-15,10,0,30,3,0,0,1,0);
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

  glutSwapBuffers();
}
void lightInitialization(void){
  float lightPosition[] = { 0, 40, 0, 0};
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
