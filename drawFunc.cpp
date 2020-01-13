#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include "drawFunc.hpp"

using namespace std;

#define GODS_EYE 300
#define RAND_MATRIX_N 25
#define RAND_MATRIX_M 9
#define RAND_OBSTACLE 100
// kidam cpp, nista clase nista oop :(
struct TACKA{
  float x;
  float y;
  float z;
};
struct OBSTACLE{
  int type;
  int position;
  float x;
};
struct CHRISTMASTREE{
  int randAngle;
  float randScale;
  float x;
  int z;
};
extern bool baltoRIP;
extern float turning;
extern float limbMovementCoef;
extern vector<vector<CHRISTMASTREE>> randMatrix;
extern vector<OBSTACLE> randObstacle;

void drawAxes(float len){
  glDisable(GL_LIGHTING);

  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(len,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,len,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,len);
  glEnd();

  glEnable(GL_LIGHTING);
}

void setNormalAndVertex(TACKA a, TACKA b, TACKA c){
  TACKA A = {b.x-a.x, b.y-a.y, b.z-a.z};
  TACKA B = {c.x-a.x, c.y-a.y, c.z-a.z};

  glNormal3f(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
  glVertex3f(a.x, a.y, a.z);
  glVertex3f(b.x, b.y, b.z);
  glVertex3f(c.x, c.y, c.z);
}

void BaltoCrashed(int firstBaltoObstacle){

  switch (randObstacle[firstBaltoObstacle].type) {
    //STEEL
    case 0:
      if(randObstacle[firstBaltoObstacle].x<11 && randObstacle[firstBaltoObstacle].x>-5){
        switch (randObstacle[firstBaltoObstacle].position) {
          case -1:
            if(turning<-5.0){
              baltoRIP=true;
              cout<<"STEEL LEFT"<<endl;
            }
            break;
          case 0:
            if(-3.0<turning && turning<3.0){
              baltoRIP=true;
              cout<<"STEEL MID"<<endl;
            }
            break;
          case 1:
            if(turning>5.0){
              baltoRIP=true;
              cout<<"STEEL RIGHT"<<endl;
            }
            break;
        }
      }
      break;
      //TREE
    case 1:
      if(randObstacle[firstBaltoObstacle].x<9 && randObstacle[firstBaltoObstacle].x>-2){
        switch (randObstacle[firstBaltoObstacle].position) {
          case -1:
            if(turning<-3.0){
              baltoRIP=true;
              cout<<"TREE LEFT"<<endl;
            }
            break;
          case 0:
            if(-5.0<turning && turning<5.0){
              baltoRIP=true;
              cout<<"TREE MID"<<endl;
            }
            break;
          case 1:
            if(turning>3.0){
              baltoRIP=true;
              cout<<"TREE RIGHT"<<endl;
            }
            break;
        }
      }
      break;
    }
}

void drawTrack(void){
  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(0,-0.5,0);
    glScalef(1000,1,24);
    glutSolidCube(1);
  glPopMatrix();

  glColor3f(1,0,0);
  glBegin(GL_LINES);
    glVertex3f(-300,0,4);
    glVertex3f(300,0,4);
    glVertex3f(-300,0,-4);
    glVertex3f(300,0,-4);
    glVertex3f(-300,0,12);
    glVertex3f(300,0,12);
    glVertex3f(-300,0,-12);
    glVertex3f(300,0,-12);
  glEnd();
}

void drawTerrain(void){
  glColor3f(0.7,0.7,0.7);
  glPushMatrix();
    glTranslatef(0,-0.5,-12);
    glRotatef(30,1,0,0);
    glScalef(1000,1,500);
    glutSolidCube(1);
  glPopMatrix();

  glColor3f(0.7,0.7,0.7);
  glPushMatrix();
    glTranslatef(0,-0.5,12);
    glRotatef(-30,1,0,0);
    glScalef(1000,1,500);
    glutSolidCube(1);
  glPopMatrix();

  for(int i=0;i<RAND_MATRIX_N;i++){
    for(int j=0;j<RAND_MATRIX_M;j++){
      glPushMatrix();
        glTranslatef(randMatrix[i][j].x,randMatrix[i][j].z/1.74-1,randMatrix[i][j].z);
        glRotatef(-randMatrix[i][j].randAngle,1,0,0);
        glScalef(randMatrix[i][j].randScale,randMatrix[i][j].randScale,randMatrix[i][j].randScale);
        drawChristmasTree(0,0,0);
      glPopMatrix();
    }
  }
  for(int i=0;i<RAND_MATRIX_N;i++){
    for(int j=0;j<RAND_MATRIX_M;j++){
      glPushMatrix();
        glTranslatef(randMatrix[i][j].x,randMatrix[i][j].z/1.74-0.2,-randMatrix[i][j].z);
        glRotatef(randMatrix[i][j].randAngle,1,0,0);
        glScalef(randMatrix[i][j].randScale,randMatrix[i][j].randScale,randMatrix[i][j].randScale);
        drawChristmasTree(0,0,0);
      glPopMatrix();
    }
  }


}
void randInitialization(void){
  srand(time(NULL));
  int k,q;
  k=-200;
  q=12;
  for(int i=0;i<RAND_MATRIX_N;i++){
    q=12;
    for(int j=0;j<RAND_MATRIX_M;j++){
      randMatrix[i][j].randAngle=rand() % 31;
      randMatrix[i][j].randScale=((float)rand()) / ((float)RAND_MAX) / 3.0 + 0.66;
      randMatrix[i][j].x=k;
      randMatrix[i][j].z=q;
      q+=15;
    }
    k+=25;
  }
  k=30;
  for(int i=0;i<RAND_OBSTACLE;i++){
    randObstacle[i].x = k;
    randObstacle[i].type = rand()%2;
    randObstacle[i].position = rand()%3 -1;
    k+=100;
  }
  //ne zelimd a prva prepreka bude na sredini
  randObstacle[0].position = -1;
}
void drawChristmasTree(float x, float y, float z){
  glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(1.5,1.5,1.5);
    glColor3f(0,0.4,0.1);
    GLUquadric* cyl = gluNewQuadric();

    glPushMatrix();
      glRotatef(-90,1,0,0);
      glTranslatef(0,0,1.5);//bilo2

      glTranslatef(0,0,8);
      glutSolidCone(1.3,1.6,12,1);
      glTranslatef(0,0,-8);

      glTranslatef(0,0,6.8);
      glutSolidCone(1.8,2.4,12,1);
      glTranslatef(0,0,-6.8);

      glTranslatef(0,0,5.4);
      glutSolidCone(2.2,2.8,12,1);
      glTranslatef(0,0,-5.4);

      glTranslatef(0,0,3.8);
      glutSolidCone(2.8,3.2,12,1);
      glTranslatef(0,0,-3.8);

      glTranslatef(0,0,2);
      glutSolidCone(3.1,3.6,12,1);
      glTranslatef(0,0,-2);

      glutSolidCone(3.4,4,12,1);
      glTranslatef(0,0,-1.5);

      glColor3f(0.3,0.15,0);
      gluCylinder(cyl,0.75,0.75,2,10,1);
      glRotatef(90,1,0,0);
    glPopMatrix();
  glPopMatrix();
  //Wire preko toga ali znatno uspori iscrtavanje

  glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(1.5,1.5,1.5);
    glColor3f(0,0,0);

    glPushMatrix();
      glRotatef(-90,1,0,0);
      glTranslatef(0,0,1.5);//bilo2

      glTranslatef(0,0,8);
      glutWireCone(1.3,1.6,12,1);
      glTranslatef(0,0,-8);

      glTranslatef(0,0,6.8);
      glutWireCone(1.8,2.4,12,1);
      glTranslatef(0,0,-6.8);

      glTranslatef(0,0,5.4);
      glutWireCone(2.2,2.8,12,1);
      glTranslatef(0,0,-5.4);

      glTranslatef(0,0,3.8);
      glutWireCone(2.8,3.2,12,1);
      glTranslatef(0,0,-3.8);

      glTranslatef(0,0,2);
      glutWireCone(3.1,3.6,12,1);
      glTranslatef(0,0,-2);

      glutWireCone(3.4,4,12,1);
      glTranslatef(0,0,-1.5);
    glPopMatrix();
  glPopMatrix();

}

void countdown(void){
  //TODO hocu da odbrojava 3 2 1.. mozda teksture
  glColor3f(1,0,0);
  glRasterPos3f(0,1,0);
  char c3 = '3';
  char c2 = '2';
  char c1 = '1';
  string sGo = "GO!!!";

  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c3);

  glutPostRedisplay();
  usleep(1000000);
  cout<<"prva sekunda"<<endl;
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c2);
  usleep(1000000);
  glutPostRedisplay();
  cout<<"druga sekunda"<<endl;
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c1);
  glutPostRedisplay();
  usleep(1000000);
  cout<<"treca sekunda"<<endl;
  for(char c : sGo){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
  }
  glutPostRedisplay();
  usleep(1000000);
}

void drawChristmasTreeObstacle(int position){

  switch (position) {
    case -1:
      glPushMatrix();
        glTranslatef(0,0.5,-12);
        glRotatef(90,1,0,0);
        glScalef(0.7,0.5,0.7);
        drawChristmasTree(0,0,0);
      glPopMatrix();
      break;
    case 0:
      glPushMatrix();
        glTranslatef(0,0.5,0);
        glScalef(0.7,0.5,0.7);
        drawChristmasTree(0,0,0);
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
        glTranslatef(0,0.5,12);
        glRotatef(-90,1,0,0);
        glScalef(0.7,0.5,0.7);
        drawChristmasTree(0,0,0);
      glPopMatrix();
      break;
  }
}

void drawSteel(void){
  glPushMatrix();
    GLUquadric* cyl=gluNewQuadric();
    float duzina=7.27;
    float visina=3.92;
    float sirina=2.04;
    TACKA a,b,c,A,B;

    glColor3f(0.2,0.2,0.2);
    glTranslatef(-duzina/2,2.37+0.1-0.79,0);

    glPushMatrix();
      glScalef(1,1,1.5);
      // desna strana
      glBegin(GL_TRIANGLES);
        // a
        a={0.00, 1.58, 0.35};
        b={0.35, 0.90, 0.35};
        c={0.89, 1.58, 0.40};
        setNormalAndVertex(a, b, c);

        // b
        a={0.00, 1.58, 0.35};
        b={0.89, 1.58, 0.40};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        // c1
        a={0.35, 0.90, 0.35};
        b={2.70, 0.33, 0.35};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // c2
        a={0.35, 0.90, 0.35};
        b={3.50, 1.20, 0.61};
        c={0.89, 1.58, 0.40};
        setNormalAndVertex(a, b, c);

        // d
        a={0.89, 1.58, 0.40};
        b={2.33, 2.00, 0.35};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        // e
        a={0.89, 1.58, 0.40};
        b={3.50, 1.20, 0.61};
        c={2.33, 2.00, 0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, 0.35};
        b={3.78, 0.00, 0.45};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, 0.45};
        b={5.06, 0.82, 0.40};
        c={4.10, 1.58, 0.55};
        setNormalAndVertex(a, b, c);

        // g2
        a={3.78, 0.00, 0.45};
        b={4.10, 1.58, 0.55};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, 0.40};
        b={5.81, 2.12, 0.35};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // h2
        a={4.10, 1.58, 0.55};
        b={5.06, 0.82, 0.40};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // t1
        a={3.50, 1.20, 0.61};
        b={4.10, 1.58, 0.55};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // t2
        a={3.50, 1.20, 0.61};
        b={5.50, 2.49, 0.45};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);

        // t3
        a={2.33, 2.00, 0.35};
        b={3.50, 1.20, 0.61};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // leva strana
      glBegin(GL_TRIANGLES);
        // a
        a={0.00, 1.58, -0.35};
        b={0.35, 0.90, -0.35};
        c={0.89, 1.58, -0.40};
        setNormalAndVertex(a, b, c);

        // b
        a={0.00, 1.58, -0.35};
        b={0.89, 1.58, -0.40};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        // c1
        a={0.35,0.90,-0.35};
        b={2.70,0.33,-0.35};
        c={3.50,1.20,-0.61};
        setNormalAndVertex(a, b, c);

        // c2
        a={0.35, 0.90, -0.35};
        b={3.50, 1.20, -0.61};
        c={0.89, 1.58, -0.40};
        setNormalAndVertex(a, b, c);

        // d
        a={0.89, 1.58, -0.40};
        b={2.33, 2.00, -0.35};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        // e
        a={0.89, 1.58, -0.40};
        b={3.50, 1.20, -0.61};
        c={2.33, 2.00, -0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, -0.45};
        c={3.50, 1.20, -0.61};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, -0.40};
        c={4.10, 1.58, -0.55};
        setNormalAndVertex(a, b, c);

        // g2
        a={3.78, 0.00, -0.45};
        b={4.10, 1.58, -0.55};
        c={3.50, 1.20, -0.61};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, -0.35};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // h2
        a={4.10, 1.58, -0.55};
        b={5.06, 0.82, -0.40};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // t1
        a={3.50, 1.20, -0.61};
        b={4.10, 1.58, -0.55};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // t2
        a={3.50, 1.20, -0.61};
        b={5.50, 2.49, -0.45};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);

        // t3
        a={2.33, 2.00, -0.35};
        b={3.50, 1.20, -0.61};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // gornja strana
      glBegin(GL_TRIANGLES);
        //  a
        a={0.35, 0.90, -0.35};
        b={0.35, 0.90, 0.35};
        c={0.00, 1.58, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.35, 0.90, -0.35};
        b={0.00, 1.58, 0.35};
        c={0.00, 1.58, -0.35};
        setNormalAndVertex(a, b, c);

        //  b
        a={0.00, 1.58, -0.35};
        b={0.00, 1.58, 0.35};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.00, 1.58, -0.35};
        b={0.89, 2.12, 0.35};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        //  d
        a={0.89, 2.12, -0.35};
        b={0.89, 2.12, 0.35};
        c={2.33, 2.00, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.89, 2.12, -0.35};
        b={2.33, 2.00, 0.35};
        c={2.33, 2.00, -0.35};
        setNormalAndVertex(a, b, c);

        //  t3
        a={2.33, 2.00, -0.35};
        b={2.33, 2.00, 0.35};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);

        a={2.33, 2.00, -0.35};
        b={5.06, 3.10, 0.35};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // donja strana idem umesto a b c -> a c b
      glBegin(GL_TRIANGLES);
        // c1
        a={0.35, 0.90, -0.35};
        b={2.70, 0.33, 0.35};
        c={0.35, 0.90, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.35, 0.90, -0.35};
        b={2.70, 0.33, -0.35};
        c={2.70, 0.33, 0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, 0.45};
        c={2.70, 0.33, 0.35};
        setNormalAndVertex(a, b, c);

        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, -0.45};
        c={3.78, 0.00, 0.45};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, 0.40};
        c={3.78, 0.00, 0.45};
        setNormalAndVertex(a, b, c);

        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, -0.40};
        c={5.06, 0.82, 0.40};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, 0.35};
        c={5.06, 0.82, 0.40};
        setNormalAndVertex(a, b, c);

        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, -0.35};
        c={5.81, 2.12, 0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // rep
      glPushMatrix();
        glTranslatef(-1.7,0.7,0);
        glRotatef(20,0,0,1);
        glRotatef(90,0,1,0);
        // duzi deo
        glutSolidCone(0.60,2.5,7,1);
        glRotatef(180,1,0,0);
        // kraci deo
        glutSolidCone(0.60,1,7,1);
      glPopMatrix();

      // glava desno
      glBegin(GL_TRIANGLES);
        //a
        a={5.50, 2.49, 0.60};
        b={5.90, 2.03, 0.40};
        c={6.10, 2.38, 0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, 0.60};
        b={6.10, 2.38, 0.35};
        c={5.70, 2.91, 0.55};
        setNormalAndVertex(a, b, c);

        //b
        a={5.50, 2.49, 0.60};
        b={5.70, 2.91, 0.55};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, 0.60};
        b={5.60, 3.92, 0.35};
        c={4.80, 3.92, 0.40};
        setNormalAndVertex(a, b, c);

        //c
        a={6.10, 2.38, 0.35};
        b={6.20, 2.80, 0.50};
        c={5.70, 2.91, 0.55};
        setNormalAndVertex(a, b, c);

        //d
        a={5.70, 2.91, 0.55};
        b={6.20, 2.80, 0.50};
        c={6.30, 3.50, 0.30};
        setNormalAndVertex(a, b, c);

        a={5.70, 2.91, 0.55};
        b={6.30, 3.50, 0.30};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, 0.35};
        b={6.30, 2.49, 0.18};
        c={6.42, 2.72, 0.30};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, 0.35};
        b={6.42, 2.72, 0.30};
        c={6.20, 2.80, 0.50};
        setNormalAndVertex(a, b, c);

        //f
        a={6.20, 2.80, 0.50};
        b={6.42, 2.72, 0.30};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);

        a={6.20,2.80,0.50};
        b={6.63,3.10,0.18};
        c={6.30,3.50,0.30};
        setNormalAndVertex(a, b, c);

        //g
        a={6.30, 2.49, 0.18};
        b={7.00, 2.49, 0.15};
        c={7.10, 2.66, 0.25};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, 0.18};
        b={7.10, 2.66, 0.25};
        c={6.42, 2.72, 0.30};
        setNormalAndVertex(a, b, c);

        //h
        a={6.42, 2.72, 0.30};
        b={7.10, 2.66, 0.25};
        c={7.18, 2.91, 0.15};
        setNormalAndVertex(a, b, c);

        a={6.42, 2.72, 0.30};
        b={7.18, 2.91, 0.15};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava levo
      glBegin(GL_TRIANGLES);
        //a
        a={5.50, 2.49, -0.60};
        b={5.90, 2.03, -0.40};
        c={6.10, 2.38, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, -0.60};
        b={6.10, 2.38, -0.35};
        c={5.70, 2.91, -0.55};
        setNormalAndVertex(a, b, c);

        //b
        a={5.50, 2.49, -0.60};
        b={5.70, 2.91, -0.55};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, -0.60};
        b={5.60, 3.92, -0.35};
        c={4.80, 3.92, -0.40};
        setNormalAndVertex(a, b, c);

        //c
        a={6.10, 2.38, -0.35};
        b={6.20, 2.80, -0.50};
        c={5.70, 2.91, -0.55};
        setNormalAndVertex(a, b, c);

        //d
        a={5.70, 2.91, -0.55};
        b={6.20, 2.80, -0.50};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);

        a={5.70, 2.91, -0.55};
        b={6.30, 3.50, -0.30};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, -0.35};
        b={6.30, 2.49, -0.18};
        c={6.42, 2.72, -0.30};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, -0.35};
        b={6.42, 2.72, -0.30};
        c={6.20, 2.80, -0.50};
        setNormalAndVertex(a, b, c);

        //f
        a={6.20, 2.80, -0.50};
        b={6.42, 2.72, -0.30};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);

        a={6.20, 2.80, -0.50};
        b={6.63, 3.10, -0.18};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);
        //g
        a={6.30, 2.49, -0.18};
        b={7.00, 2.49, -0.15};
        c={7.10, 2.66, -0.25};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, -0.18};
        b={7.10, 2.66, -0.25};
        c={6.42, 2.72, -0.30};
        setNormalAndVertex(a, b, c);

        //h
        a={6.42, 2.72, -0.30};
        b={7.10, 2.66, -0.25};
        c={7.18, 2.91, -0.15};
        setNormalAndVertex(a, b, c);

        a={6.42, 2.72, -0.30};
        b={7.18, 2.91, -0.15};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava gore
      glBegin(GL_TRIANGLES);
        //b
        a={4.80, 3.92, -0.40};
        b={4.80, 3.92, 0.40};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        a={4.80, 3.92, -0.40};
        b={5.60, 3.92, 0.35};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        //d
        a={5.60, 3.92, -0.35};
        b={5.60, 3.92, 0.35};
        c={6.30, 3.50, 0.30};
        setNormalAndVertex(a, b, c);

        a={5.60, 3.92, -0.35};
        b={6.30, 3.50, 0.30};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);

        //f
        a={6.30, 3.50, -0.30};
        b={6.30, 3.50, 0.30};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);

        a={6.30, 3.50, -0.30};
        b={6.63, 3.10, 0.18};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);

        //h
        a={6.63, 3.10, -0.18};
        b={6.63, 3.10, 0.18};
        c={7.18, 2.91, 0.15};
        setNormalAndVertex(a, b, c);

        a={6.63, 3.10, -0.18};
        b={7.18, 2.91, 0.15};
        c={7.18, 2.91, -0.15};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava dole
      glBegin(GL_TRIANGLES);
        //a
        a={5.90, 2.03, 0.40};
        b={5.90, 2.03, -0.40};
        c={6.10, 2.38, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.90, 2.03, 0.40 };
        b={6.10, 2.38, -0.35 };
        c={6.10, 2.38, 0.35 };
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, 0.35};
        b={6.10, 2.38, -0.35};
        c={6.30, 2.49, -0.18};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, 0.35};
        b={6.30, 2.49, -0.18};
        c={6.30, 2.49, 0.18};
        setNormalAndVertex(a, b, c);

        //g
        a={6.30, 2.49, 0.18};
        b={6.30, 2.49, -0.18};
        c={7.00, 2.49, -0.15};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, 0.18};
        b={7.00, 2.49, -0.15};
        c={7.00, 2.49, 0.15};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava pozadi
      glBegin(GL_POLYGON);
        a = {5.90, 2.03, 0.40};
        b = {5.50, 2.49, 0.60};
        c = {4.80, 3.92, 0.40};
        A = {b.x-a.x, b.y-a.y, b.z-a.z};
        B = {c.x-a.x, c.y-a.y, c.z-a.z};
        glNormal3f(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);

        glVertex3f(4.80,3.92,0.40);
        glVertex3f(5.50,2.49,0.60);
        glVertex3f(5.90,2.03,0.40);
        glVertex3f(5.90,2.03,-0.40);
        glVertex3f(5.50,2.49,-0.60);
        glVertex3f(4.80,3.92,-0.40);
      glEnd();

      // nos
      glBegin(GL_POLYGON);
        a = {7.00, 2.49, 0.15};
        b = {7.00, 2.49, -0.15};
        c = {7.10, 2.66, -0.25};
        A = {b.x-a.x, b.y-a.y, b.z-a.z};
        B = {c.x-a.x, c.y-a.y, c.z-a.z};
        glNormal3f(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);

        glVertex3f(7.00,2.49,0.15);
        glVertex3f(7.10,2.66,0.25);
        glVertex3f(7.18,2.91,0.15);
        glVertex3f(7.18,2.91,-0.15);
        glVertex3f(7.10,2.66,-0.25);
        glVertex3f(7.00,2.49,-0.15);
      glEnd();

      // usi
      glPushMatrix();
        glTranslatef(5.50,3.2,-0.30);
        glRotatef(15,0,0,1);
        glRotatef(-110,1,0,0);
        glutSolidCone(0.3,1.43,3,1);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(5.50,3.2,0.30);
        glRotatef(15,0,0,1);
        glRotatef(-70,1,0,0);
        glutSolidCone(0.3,1.43,3,1);
      glPopMatrix();
    glPopMatrix();

    // desna zadnja
    glPushMatrix();
      glTranslatef(0.89,1,0.42);

      // batak
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37+0.21,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37-0.21,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      // zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      // prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // leva zadnja
    glPushMatrix();
      glTranslatef(0.89,1,-0.42);

      // butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37+0.21,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37-0.21,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      // zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // desna prednja
    glPushMatrix();
      glTranslatef(4.10,0.79,0.67);
      // butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      //zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // leva prednja
    glPushMatrix();
      glTranslatef(4.10,0.79,-0.67);
      //butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37,8,1);
      glPopMatrix();

      //nogica
      glTranslatef(0.3,-2.37,0);
      glScalef(1,1,2);

      //sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      //zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();
  glPopMatrix();
}

void drawSteelObstacle(int position){
  switch (position) {
    case -1:
      glPushMatrix();
        glTranslatef(0,0,-8);
        glRotatef(180,0,1,0);
        drawSteel();
      glPopMatrix();
      break;
    case 0:
      glPushMatrix();
        glRotatef(180,0,1,0);
        drawSteel();
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
        glTranslatef(0,0,8);
        glRotatef(180,0,1,0);
        drawSteel();
      glPopMatrix();
      break;
  }
}

void drawObstacles(void){
  for(int j=0;j<RAND_OBSTACLE;j++){
    drawObstacle(randObstacle[j].x,randObstacle[j].type,randObstacle[j].position);
  }
}

void drawObstacle(float x, int type, int position){
  switch (type) {
    case 0:
      glPushMatrix();
        glTranslatef(x,0,0);
        drawSteelObstacle(position);
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
        glTranslatef(x,0,0);
        drawChristmasTreeObstacle(position);
      glPopMatrix();
      break;
  }
}

void drawBalto(int baltoPosition){
  glPushMatrix();
    glTranslatef(0,0,turning);
    GLUquadric* cyl=gluNewQuadric();
    float duzina=7.27;
    float visina=3.92;
    float sirina=2.04;
    TACKA a,b,c,A,B;

    glColor3f(0.1,0.1,0.8);
    if(baltoRIP){
    glColor3f(1,0,0);
    }
    glTranslatef(0,2.37+0.1-0.79,0);

    glPushMatrix();
      glScalef(1,1,1.5);
      // desna strana
      glBegin(GL_TRIANGLES);
        // a
        a={0.00, 1.58, 0.35};
        b={0.35, 0.90, 0.35};
        c={0.89, 1.58, 0.40};
        setNormalAndVertex(a, b, c);

        // b
        a={0.00, 1.58, 0.35};
        b={0.89, 1.58, 0.40};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        // c1
        a={0.35, 0.90, 0.35};
        b={2.70, 0.33, 0.35};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // c2
        a={0.35, 0.90, 0.35};
        b={3.50, 1.20, 0.61};
        c={0.89, 1.58, 0.40};
        setNormalAndVertex(a, b, c);

        // d
        a={0.89, 1.58, 0.40};
        b={2.33, 2.00, 0.35};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        // e
        a={0.89, 1.58, 0.40};
        b={3.50, 1.20, 0.61};
        c={2.33, 2.00, 0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, 0.35};
        b={3.78, 0.00, 0.45};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, 0.45};
        b={5.06, 0.82, 0.40};
        c={4.10, 1.58, 0.55};
        setNormalAndVertex(a, b, c);

        // g2
        a={3.78, 0.00, 0.45};
        b={4.10, 1.58, 0.55};
        c={3.50, 1.20, 0.61};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, 0.40};
        b={5.81, 2.12, 0.35};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // h2
        a={4.10, 1.58, 0.55};
        b={5.06, 0.82, 0.40};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // t1
        a={3.50, 1.20, 0.61};
        b={4.10, 1.58, 0.55};
        c={5.50, 2.49, 0.45};
        setNormalAndVertex(a, b, c);

        // t2
        a={3.50, 1.20, 0.61};
        b={5.50, 2.49, 0.45};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);

        // t3
        a={2.33, 2.00, 0.35};
        b={3.50, 1.20, 0.61};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // leva strana
      glBegin(GL_TRIANGLES);
        // a
        a={0.00, 1.58, -0.35};
        b={0.35, 0.90, -0.35};
        c={0.89, 1.58, -0.40};
        setNormalAndVertex(a, b, c);

        // b
        a={0.00, 1.58, -0.35};
        b={0.89, 1.58, -0.40};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        // c1
        a={0.35,0.90,-0.35};
        b={2.70,0.33,-0.35};
        c={3.50,1.20,-0.61};
        setNormalAndVertex(a, b, c);

        // c2
        a={0.35, 0.90, -0.35};
        b={3.50, 1.20, -0.61};
        c={0.89, 1.58, -0.40};
        setNormalAndVertex(a, b, c);

        // d
        a={0.89, 1.58, -0.40};
        b={2.33, 2.00, -0.35};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        // e
        a={0.89, 1.58, -0.40};
        b={3.50, 1.20, -0.61};
        c={2.33, 2.00, -0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, -0.45};
        c={3.50, 1.20, -0.61};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, -0.40};
        c={4.10, 1.58, -0.55};
        setNormalAndVertex(a, b, c);

        // g2
        a={3.78, 0.00, -0.45};
        b={4.10, 1.58, -0.55};
        c={3.50, 1.20, -0.61};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, -0.35};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // h2
        a={4.10, 1.58, -0.55};
        b={5.06, 0.82, -0.40};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // t1
        a={3.50, 1.20, -0.61};
        b={4.10, 1.58, -0.55};
        c={5.50, 2.49, -0.45};
        setNormalAndVertex(a, b, c);

        // t2
        a={3.50, 1.20, -0.61};
        b={5.50, 2.49, -0.45};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);

        // t3
        a={2.33, 2.00, -0.35};
        b={3.50, 1.20, -0.61};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // gornja strana
      glBegin(GL_TRIANGLES);
        //  a
        a={0.35, 0.90, -0.35};
        b={0.35, 0.90, 0.35};
        c={0.00, 1.58, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.35, 0.90, -0.35};
        b={0.00, 1.58, 0.35};
        c={0.00, 1.58, -0.35};
        setNormalAndVertex(a, b, c);

        //  b
        a={0.00, 1.58, -0.35};
        b={0.00, 1.58, 0.35};
        c={0.89, 2.12, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.00, 1.58, -0.35};
        b={0.89, 2.12, 0.35};
        c={0.89, 2.12, -0.35};
        setNormalAndVertex(a, b, c);

        //  d
        a={0.89, 2.12, -0.35};
        b={0.89, 2.12, 0.35};
        c={2.33, 2.00, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.89, 2.12, -0.35};
        b={2.33, 2.00, 0.35};
        c={2.33, 2.00, -0.35};
        setNormalAndVertex(a, b, c);

        //  t3
        a={2.33, 2.00, -0.35};
        b={2.33, 2.00, 0.35};
        c={5.06, 3.10, 0.35};
        setNormalAndVertex(a, b, c);

        a={2.33, 2.00, -0.35};
        b={5.06, 3.10, 0.35};
        c={5.06, 3.10, -0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // donja strana idem umesto a b c -> a c b
      glBegin(GL_TRIANGLES);
        // c1
        a={0.35, 0.90, -0.35};
        b={2.70, 0.33, 0.35};
        c={0.35, 0.90, 0.35};
        setNormalAndVertex(a, b, c);

        a={0.35, 0.90, -0.35};
        b={2.70, 0.33, -0.35};
        c={2.70, 0.33, 0.35};
        setNormalAndVertex(a, b, c);

        // f
        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, 0.45};
        c={2.70, 0.33, 0.35};
        setNormalAndVertex(a, b, c);

        a={2.70, 0.33, -0.35};
        b={3.78, 0.00, -0.45};
        c={3.78, 0.00, 0.45};
        setNormalAndVertex(a, b, c);

        // g1
        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, 0.40};
        c={3.78, 0.00, 0.45};
        setNormalAndVertex(a, b, c);

        a={3.78, 0.00, -0.45};
        b={5.06, 0.82, -0.40};
        c={5.06, 0.82, 0.40};
        setNormalAndVertex(a, b, c);

        // h1
        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, 0.35};
        c={5.06, 0.82, 0.40};
        setNormalAndVertex(a, b, c);

        a={5.06, 0.82, -0.40};
        b={5.81, 2.12, -0.35};
        c={5.81, 2.12, 0.35};
        setNormalAndVertex(a, b, c);
      glEnd();

      // rep
      glPushMatrix();
        glTranslatef(-1.7,0.7,0);
        glRotatef(20,0,0,1);
        glRotatef(90,0,1,0);
        // duzi deo
        glutSolidCone(0.40,2.5,7,1);
        glRotatef(180,1,0,0);
        // kraci deo
        glutSolidCone(0.40,1,7,1);
      glPopMatrix();

      // glava desno
      glBegin(GL_TRIANGLES);
        //a
        a={5.50, 2.49, 0.60};
        b={5.90, 2.03, 0.40};
        c={6.10, 2.38, 0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, 0.60};
        b={6.10, 2.38, 0.35};
        c={5.70, 2.91, 0.55};
        setNormalAndVertex(a, b, c);

        //b
        a={5.50, 2.49, 0.60};
        b={5.70, 2.91, 0.55};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, 0.60};
        b={5.60, 3.92, 0.35};
        c={4.80, 3.92, 0.40};
        setNormalAndVertex(a, b, c);

        //c
        a={6.10, 2.38, 0.35};
        b={6.20, 2.80, 0.50};
        c={5.70, 2.91, 0.55};
        setNormalAndVertex(a, b, c);

        //d
        a={5.70, 2.91, 0.55};
        b={6.20, 2.80, 0.50};
        c={6.30, 3.50, 0.30};
        setNormalAndVertex(a, b, c);

        a={5.70, 2.91, 0.55};
        b={6.30, 3.50, 0.30};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, 0.35};
        b={6.30, 2.49, 0.18};
        c={6.42, 2.72, 0.30};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, 0.35};
        b={6.42, 2.72, 0.30};
        c={6.20, 2.80, 0.50};
        setNormalAndVertex(a, b, c);

        //f
        a={6.20, 2.80, 0.50};
        b={6.42, 2.72, 0.30};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);

        a={6.20,2.80,0.50};
        b={6.63,3.10,0.18};
        c={6.30,3.50,0.30};
        setNormalAndVertex(a, b, c);

        //g
        a={6.30, 2.49, 0.18};
        b={7.00, 2.49, 0.15};
        c={7.10, 2.66, 0.25};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, 0.18};
        b={7.10, 2.66, 0.25};
        c={6.42, 2.72, 0.30};
        setNormalAndVertex(a, b, c);

        //h
        a={6.42, 2.72, 0.30};
        b={7.10, 2.66, 0.25};
        c={7.18, 2.91, 0.15};
        setNormalAndVertex(a, b, c);

        a={6.42, 2.72, 0.30};
        b={7.18, 2.91, 0.15};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava levo
      glBegin(GL_TRIANGLES);
        //a
        a={5.50, 2.49, -0.60};
        b={5.90, 2.03, -0.40};
        c={6.10, 2.38, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, -0.60};
        b={6.10, 2.38, -0.35};
        c={5.70, 2.91, -0.55};
        setNormalAndVertex(a, b, c);

        //b
        a={5.50, 2.49, -0.60};
        b={5.70, 2.91, -0.55};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.50, 2.49, -0.60};
        b={5.60, 3.92, -0.35};
        c={4.80, 3.92, -0.40};
        setNormalAndVertex(a, b, c);

        //c
        a={6.10, 2.38, -0.35};
        b={6.20, 2.80, -0.50};
        c={5.70, 2.91, -0.55};
        setNormalAndVertex(a, b, c);

        //d
        a={5.70, 2.91, -0.55};
        b={6.20, 2.80, -0.50};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);

        a={5.70, 2.91, -0.55};
        b={6.30, 3.50, -0.30};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, -0.35};
        b={6.30, 2.49, -0.18};
        c={6.42, 2.72, -0.30};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, -0.35};
        b={6.42, 2.72, -0.30};
        c={6.20, 2.80, -0.50};
        setNormalAndVertex(a, b, c);

        //f
        a={6.20, 2.80, -0.50};
        b={6.42, 2.72, -0.30};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);

        a={6.20, 2.80, -0.50};
        b={6.63, 3.10, -0.18};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);
        //g
        a={6.30, 2.49, -0.18};
        b={7.00, 2.49, -0.15};
        c={7.10, 2.66, -0.25};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, -0.18};
        b={7.10, 2.66, -0.25};
        c={6.42, 2.72, -0.30};
        setNormalAndVertex(a, b, c);

        //h
        a={6.42, 2.72, -0.30};
        b={7.10, 2.66, -0.25};
        c={7.18, 2.91, -0.15};
        setNormalAndVertex(a, b, c);

        a={6.42, 2.72, -0.30};
        b={7.18, 2.91, -0.15};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava gore
      glBegin(GL_TRIANGLES);
        //b
        a={4.80, 3.92, -0.40};
        b={4.80, 3.92, 0.40};
        c={5.60, 3.92, 0.35};
        setNormalAndVertex(a, b, c);

        a={4.80, 3.92, -0.40};
        b={5.60, 3.92, 0.35};
        c={5.60, 3.92, -0.35};
        setNormalAndVertex(a, b, c);

        //d
        a={5.60, 3.92, -0.35};
        b={5.60, 3.92, 0.35};
        c={6.30, 3.50, 0.30};
        setNormalAndVertex(a, b, c);

        a={5.60, 3.92, -0.35};
        b={6.30, 3.50, 0.30};
        c={6.30, 3.50, -0.30};
        setNormalAndVertex(a, b, c);

        //f
        a={6.30, 3.50, -0.30};
        b={6.30, 3.50, 0.30};
        c={6.63, 3.10, 0.18};
        setNormalAndVertex(a, b, c);

        a={6.30, 3.50, -0.30};
        b={6.63, 3.10, 0.18};
        c={6.63, 3.10, -0.18};
        setNormalAndVertex(a, b, c);

        //h
        a={6.63, 3.10, -0.18};
        b={6.63, 3.10, 0.18};
        c={7.18, 2.91, 0.15};
        setNormalAndVertex(a, b, c);

        a={6.63, 3.10, -0.18};
        b={7.18, 2.91, 0.15};
        c={7.18, 2.91, -0.15};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava dole
      glBegin(GL_TRIANGLES);
        //a
        a={5.90, 2.03, 0.40};
        b={5.90, 2.03, -0.40};
        c={6.10, 2.38, -0.35};
        setNormalAndVertex(a, b, c);

        a={5.90, 2.03, 0.40 };
        b={6.10, 2.38, -0.35 };
        c={6.10, 2.38, 0.35 };
        setNormalAndVertex(a, b, c);

        //e
        a={6.10, 2.38, 0.35};
        b={6.10, 2.38, -0.35};
        c={6.30, 2.49, -0.18};
        setNormalAndVertex(a, b, c);

        a={6.10, 2.38, 0.35};
        b={6.30, 2.49, -0.18};
        c={6.30, 2.49, 0.18};
        setNormalAndVertex(a, b, c);

        //g
        a={6.30, 2.49, 0.18};
        b={6.30, 2.49, -0.18};
        c={7.00, 2.49, -0.15};
        setNormalAndVertex(a, b, c);

        a={6.30, 2.49, 0.18};
        b={7.00, 2.49, -0.15};
        c={7.00, 2.49, 0.15};
        setNormalAndVertex(a, b, c);
      glEnd();

      // glava pozadi
      glBegin(GL_POLYGON);
        a = {5.90, 2.03, 0.40};
        b = {5.50, 2.49, 0.60};
        c = {4.80, 3.92, 0.40};
        A = {b.x-a.x, b.y-a.y, b.z-a.z};
        B = {c.x-a.x, c.y-a.y, c.z-a.z};
        glNormal3f(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);

        glVertex3f(4.80,3.92,0.40);
        glVertex3f(5.50,2.49,0.60);
        glVertex3f(5.90,2.03,0.40);
        glVertex3f(5.90,2.03,-0.40);
        glVertex3f(5.50,2.49,-0.60);
        glVertex3f(4.80,3.92,-0.40);
      glEnd();

      // nos
      glBegin(GL_POLYGON);
        a = {7.00, 2.49, 0.15};
        b = {7.00, 2.49, -0.15};
        c = {7.10, 2.66, -0.25};
        A = {b.x-a.x, b.y-a.y, b.z-a.z};
        B = {c.x-a.x, c.y-a.y, c.z-a.z};
        glNormal3f(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);

        glVertex3f(7.00,2.49,0.15);
        glVertex3f(7.10,2.66,0.25);
        glVertex3f(7.18,2.91,0.15);
        glVertex3f(7.18,2.91,-0.15);
        glVertex3f(7.10,2.66,-0.25);
        glVertex3f(7.00,2.49,-0.15);
      glEnd();

      // usi
      glPushMatrix();
        glTranslatef(5.50,3.2,-0.30);
        glRotatef(15,0,0,1);
        glRotatef(-110,1,0,0);
        glutSolidCone(0.3,1.43,3,1);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(5.50,3.2,0.30);
        glRotatef(15,0,0,1);
        glRotatef(-70,1,0,0);
        glutSolidCone(0.3,1.43,3,1);
      glPopMatrix();
    glPopMatrix();

    // desna zadnja
    glPushMatrix();
      glTranslatef(0.89,1,0.42);
      glRotatef(-limbMovementCoef,0,0,1);

      // batak
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37+0.21,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37-0.21,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      // zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      // prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // leva zadnja
    glPushMatrix();
      glTranslatef(0.89,1,-0.42);
      glRotatef(limbMovementCoef,0,0,1);

      // butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37+0.21,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37-0.21,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      // zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // desna prednja
    glPushMatrix();
      glTranslatef(4.10,0.79,0.67);
      glRotatef(limbMovementCoef,0,0,1);
      // butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37,8,1);
      glPopMatrix();

      // nogica
      glTranslatef(0.3,-2.37,0);
      glScalef(1,1,2);

      // sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      //zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // leva prednja
    glPushMatrix();
      glTranslatef(4.10,0.79,-0.67);
      glRotatef(-limbMovementCoef,0,0,1);
      //butina
      glPushMatrix();
        glutSolidSphere(0.5,20,20);
        glRotatef(90,1,0,0);
        gluCylinder(cyl,0.5,0.1,2.37,8,1);
      glPopMatrix();

      //nogica
      glTranslatef(0.3,-2.37,0);
      glScalef(1,1,2);

      //sapa
      glPushMatrix();
        glScalef(2,1,1);
        glTranslatef(0.1,0,0);
        glutSolidCube(0.2);
      glPopMatrix();

      //zglob
      glRotatef(45,1,0,0);
      glRotatef(-90,0,1,0);
      gluCylinder(cyl,0.15,0.1,0.3,4,1);
      glRotatef(90,0,1,0);
      glRotatef(-45,1,0,0);

      //prsti
      glTranslatef(0.4,0,0);
      glRotatef(45,1,0,0);
      glRotatef(90,0,1,0);
      glutSolidCone(0.15,0.2,4,1);
    glPopMatrix();

    // hitbox
    glColor3f(1,1,0);
    glTranslatef(duzina/2,visina/2,0);
    glScalef(duzina,visina,sirina);
    glutWireCube(1);
  glPopMatrix();
}
