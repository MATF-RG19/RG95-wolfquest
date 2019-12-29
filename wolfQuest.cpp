#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <GL/glut.h>
#include "drawFunc.hpp"

using namespace std;

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define LEN 100

static int windowWidth;
static int windowHeight;

static float animationParameter = 0;
static float animationOngoing = 0;
static float descending = 0;
float limbMovementCoef = 0;

// callback funkcije
static void onKeyboard(unsigned char key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int id);

static void lightInitialization(void);
static void enableOpenglOptions(void);

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  // Postavljanje prozora
  glutInitWindowSize(1200, 1000);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Wolf Quest");

  // Registrovanje callback funkcija
  glutKeyboardFunc(onKeyboard);
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);

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
  gluPerspective(60, (float) width / height, 1, 200);
}

void onKeyboard(unsigned char key, int x, int y){
  switch(key){
    case 'r':
      animationParameter = 0;
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

void onTimer(int id){
    if(id == TIMER_ID){
      animationParameter++;
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
  // gluLookAt(-10,10,0,5,3,0,0,1,0);
  // u njusku
  // gluLookAt(20,2,0,5,3,0,0,1,0);
  // fino
  // gluLookAt(20*sin(animationParameter/360),7,20*cos(animationParameter/360),4,2,0,0,1,0);
  gluLookAt(40*sin(animationParameter/360),15,40*cos(animationParameter/360),0,0,0,0,1,0);
  // gluLookAt(4,7,10,4,2,0,0,1,0);
  // gluLookAt(30,4,30,0,0,0,0,1,0);

  drawAxes(LEN);

  for(int i=-100;i<=100;i+=30)
    for(int j=-100;j<=50;j+=30)
      drawChristmasTree(i,0,j);

  drawBalto();

  drawTrack();

  glutSwapBuffers();
}
void lightInitialization(void){
  float lightPosition[] = { 10, 10, 10, 0};
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
