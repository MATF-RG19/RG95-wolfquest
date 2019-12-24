#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <GL/glut.h>

using namespace std;

//def tacka
struct TACKA{
  float x;
  float y;
  float z;
};

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define LEN 100
// callback funkcije
static void onKeyboard(unsigned char key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);

static void lightInitialization(void);
static void enableOpenglOptions(void);
static void drawAxes(float len);
static void drawBalto(void);

static int windowWidth;
static int windowHeight;

static float animationParameter = 0;
static float animationOngoing = 0;

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
  gluPerspective(60, (float) width / height, 1, 100);
}

void onKeyboard(unsigned char key, int x, int y){
  switch (key){
    case 27:
      exit(0);
      break;
  }
}

void onDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

  // Postavljanje pogleda
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // gluLookAt(20,5,0,5,3,0,0,1,0);
  gluLookAt(4,7,10,4,2,0,0,1,0);

  drawAxes(LEN);

  glPushMatrix();
    glScalef(1,1,1.7);
    drawBalto();
  glPopMatrix();

  glutSwapBuffers();
}

void lightInitialization(void){
  float lightPosition[] = { 8, 8, 0, 0};
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
//----------------------------------------------------------------
float duzina=7.27;
float visina=3.92;
float sirina=2.04;
void setNormalAndVertex(TACKA a,TACKA b,TACKA c){
  TACKA A={b.x-a.x,b.y-a.y,b.z-a.z};
  TACKA B={c.x-a.x,c.y-a.y,c.z-a.z};

  glNormal3f(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);
  glVertex3f(a.x,a.y,a.z);
  glVertex3f(b.x,b.y,b.z);
  glVertex3f(c.x,c.y,c.z);
}
TACKA a,b,c;
void drawBalto(void){

  glColor3f(0.1,0.1,0.8);
  glPointSize(5);

  // right
  glBegin(GL_TRIANGLES);
    // a
    a={0,1.58,0.35};
    b={0.35,0.90,0.35};
    c={0.89,1.58,0.40};
    setNormalAndVertex(a,b,c);
    // b
    a={0,1.58,0.35 };
    b={0.89,1.58,0.40 };
    c={ 0.89,2.12,0.35};
    setNormalAndVertex(a,b,c);
    // c1
    a={0.35,0.90,0.35 };
    b={ 2.70,0.33,0.35};
    c={ 3.50,1.20,0.61};
    setNormalAndVertex(a,b,c);
    // c2
    a={ 0.35,0.90,0.35};
    b={3.50,1.20,0.61 };
    c={0.89,1.58,0.40 };
    setNormalAndVertex(a,b,c);
    // d
    a={ 0.89,1.58,0.40};
    b={ 2.33,2.0,0.35};
    c={ 0.89,2.12,0.35};
    setNormalAndVertex(a,b,c);

    // e
    a={ 0.89,1.58,0.40};
    b={3.50,1.20,0.61 };
    c={2.33,2.0,0.35 };
    setNormalAndVertex(a,b,c);

    // f
    a={2.70,0.33,0.35 };
    b={ 3.78,0,0.45};
    c={ 3.50,1.20,0.61};
    setNormalAndVertex(a,b,c);

    // g1
    a={ 3.78,0,0.45};
    b={ 5.06,0.82,0.40};
    c={4.10,1.58,0.55 };
    setNormalAndVertex(a,b,c);

    // g2
    a={ 3.78,0,0.45};
    b={4.10,1.58,0.55 };
    c={3.50,1.20,0.61 };
    setNormalAndVertex(a,b,c);

    // h1
    a={ 5.06,0.82,0.40};
    b={5.81,2.12,0.35 };
    c={ 5.50,2.49,0.45};
    setNormalAndVertex(a,b,c);

    // h2
    a={4.10,1.58,0.55 };
    b={5.06,0.82,0.40 };
    c={ 5.50,2.49,0.45};
    setNormalAndVertex(a,b,c);
    // t1
    a={3.50,1.20,0.61 };
    b={4.10,1.58,0.55 };
    c={5.50,2.49,0.45 };
    setNormalAndVertex(a,b,c);

    // t2
    a={ 3.50,1.20,0.61};
    b={5.50,2.49,0.45 };
    c={ 5.06,3.10,0.35};
    setNormalAndVertex(a,b,c);

    // t3
    a={ 2.33,2.0,0.35};
    b={3.50,1.20,0.61 };
    c={ 5.06,3.10,0.35};
    setNormalAndVertex(a,b,c);

  glEnd();
  // left

  glBegin(GL_TRIANGLES);
    // a
    a={0,1.58,-0.35};
    b={0.35,0.90,-0.35};
    c={0.89,1.58,-0.40};
    setNormalAndVertex(a,b,c);
    // b
    a={0,1.58,-0.35 };
    b={0.89,1.58,-0.40 };
    c={ 0.89,2.12,-0.35};
    setNormalAndVertex(a,b,c);
    // c1
    a={0.35,0.90,-0.35 };
    b={ 2.70,0.33,-0.35};
    c={ 3.50,1.20,-0.61};
    setNormalAndVertex(a,b,c);
    // c2
    a={ 0.35,0.90,-0.35};
    b={3.50,1.20,-0.61 };
    c={0.89,1.58,-0.40 };
    setNormalAndVertex(a,b,c);
    // d
    a={ 0.89,1.58,-0.40};
    b={ 2.33,2.0,-0.35};
    c={ 0.89,2.12,-0.35};
    setNormalAndVertex(a,b,c);

    // e
    a={ 0.89,1.58,-0.40};
    b={3.50,1.20,-0.61 };
    c={2.33,2.0,-0.35 };
    setNormalAndVertex(a,b,c);

    // f
    a={2.70,0.33,-0.35 };
    b={ 3.78,0,-0.45};
    c={ 3.50,1.20,-0.61};
    setNormalAndVertex(a,b,c);

    // g1
    a={ 3.78,0,-0.45};
    b={ 5.06,0.82,-0.40};
    c={4.10,1.58,-0.55 };
    setNormalAndVertex(a,b,c);

    // g2
    a={ 3.78,0,-0.45};
    b={4.10,1.58,-0.55 };
    c={3.50,1.20,-0.61 };
    setNormalAndVertex(a,b,c);

    // h1
    a={ 5.06,0.82,-0.40};
    b={5.81,2.12,-0.35 };
    c={ 5.50,2.49,-0.45};
    setNormalAndVertex(a,b,c);

    // h2
    a={4.10,1.58,-0.55 };
    b={5.06,0.82,-0.40 };
    c={ 5.50,2.49,-0.45};
    setNormalAndVertex(a,b,c);
    // t1
    a={3.50,1.20,-0.61 };
    b={4.10,1.58,-0.55 };
    c={5.50,2.49,-0.45 };
    setNormalAndVertex(a,b,c);

    // t2
    a={ 3.50,1.20,-0.61};
    b={5.50,2.49,-0.45 };
    c={ 5.06,3.10,-0.35};
    setNormalAndVertex(a,b,c);

    // t3
    a={ 2.33,2.0,-0.35};
    b={3.50,1.20,-0.61 };
    c={ 5.06,3.10,-0.35};
    setNormalAndVertex(a,b,c);

  glEnd();


  //  top
  glBegin(GL_TRIANGLES);
    //  a
    a={0.35,0.90,-0.35 };
    b={ 0.35,0.90,0.35};
    c={ 0,1.58,0.35};
    setNormalAndVertex(a,b,c);

    a={0.35,0.90,-0.35 };
    b={0,1.58,0.35 };
    c={0,1.58,-0.35 };
    setNormalAndVertex(a,b,c);

    //  b
    a={ 0,1.58,-0.35};
    b={ 0,1.58,0.35};
    c={ 0.89,2.12,0.35};
    setNormalAndVertex(a,b,c);

    a={0,1.58,-0.35 };
    b={0.89,2.12,0.35 };
    c={0.89,2.12,-0.35 };
    setNormalAndVertex(a,b,c);
    //  d
    a={0.89,2.12,-0.35 };
    b={0.89,2.12,0.35 };
    c={2.33,2.0,0.35 };
    setNormalAndVertex(a,b,c);

    a={ 0.89,2.12,-0.35};
    b={2.33,2.0,0.35 };
    c={ 2.33,2.0,-0.35};
    setNormalAndVertex(a,b,c);

    //  t3
    a={2.33,2.0,-0.35 };
    b={ 2.33,2.0,0.35};
    c={5.06,3.10,0.35 };
    setNormalAndVertex(a,b,c);

    a={ 2.33,2.0,-0.35};
    b={ 5.06,3.10,0.35};
    c={5.06,3.10,-0.35 };
    setNormalAndVertex(a,b,c);

  glEnd();
  //bottom KOPIRAM TAKO STO IDEM umesto a b c acb
  glBegin(GL_TRIANGLES);
    // c1
    a={0.35,0.90,-0.35 };
    b={ 2.70,0.33,0.35};
    c={ 0.35,0.90,0.35};
    setNormalAndVertex(a,b,c);


    a={0.35,0.90,-0.35 };
    b={ 2.70,0.33,-0.35};
    c={ 2.70,0.33,0.35};
    setNormalAndVertex(a,b,c);

    // f
    a={2.70,0.33,-0.35 };
    b={3.78,0,0.45};
    c={2.70,0.33,0.35 };
    setNormalAndVertex(a,b,c);


    a={ 2.70,0.33,-0.35};
    b={ 3.78,0,-0.45};
    c={3.78,0,0.45 };
    setNormalAndVertex(a,b,c);

    // g1
    a={3.78,0,-0.45 };
    b={5.06,0.82,0.40 };
    c={ 3.78,0,0.45};
    setNormalAndVertex(a,b,c);


    a={ 3.78,0,-0.45};
    b={5.06,0.82,-0.40 };
    c={5.06,0.82,0.40};
    setNormalAndVertex(a,b,c);

    // h1
    a={ 5.06,0.82,-0.40};
    b={ 5.81,2.12,0.35};
    c={5.06,0.82,0.40 };
    setNormalAndVertex(a,b,c);


    a={5.06,0.82,-0.40 };
    b={5.81,2.12,-0.35 };
    c={5.81,2.12,0.35 };
    setNormalAndVertex(a,b,c);

  glEnd();
  // rep
  glPushMatrix();
    glTranslatef(-1.7,0.7,0);
    glRotatef(20,0,0,1);
    glRotatef(90,0,1,0);
    glutSolidCone(0.60,2.5,7,1);
    glRotatef(180,1,0,0);
    glutSolidCone(0.60,1,7,1);
  glPopMatrix();

  // glava
  glColor3f(0.1,0.1,0.8);
  glBegin(GL_TRIANGLES);
    //a
    a={5.50,2.49,0.60};
    b={5.90,2.03,0.40 };
    c={6.10,2.38,0.35 };
    setNormalAndVertex(a,b,c);

    a={5.50,2.49,0.60};
    b={6.10,2.38,0.35};
    c={5.70,2.91,0.55};
    setNormalAndVertex(a,b,c);
    //b
    a={5.50,2.49,0.60};
    b={5.70,2.91,0.55};
    c={5.60,3.92,0.35};
    setNormalAndVertex(a,b,c);

    a={5.50,2.49,0.60};
    b={5.60,3.92,0.35};
    c={4.80,3.92,0.40};
    setNormalAndVertex(a,b,c);

    //c
    a={6.10,2.38,0.35};
    b={6.20,2.80,0.50};
    c={5.70,2.91,0.55};
    setNormalAndVertex(a,b,c);
    //d
    a={5.70,2.91,0.55};
    b={6.20,2.80,0.50};
    c={6.30,3.50,0.30};
    setNormalAndVertex(a,b,c);
    a={5.70,2.91,0.55};
    b={6.30,3.50,0.30};
    c={5.60,3.92,0.35};
    setNormalAndVertex(a,b,c);
    //e
    a={6.10,2.38,0.35};
    b={6.30,2.49,0.18};
    c={6.42,2.72,0.30};
    setNormalAndVertex(a,b,c);
    a={6.10,2.38,0.35};
    b={6.42,2.72,0.30};
    c={6.20,2.80,0.50};
    setNormalAndVertex(a,b,c);
    //f
    a={6.20,2.80,0.50};
    b={6.42,2.72,0.30};
    c={6.63,3.10,0.18};
    setNormalAndVertex(a,b,c);
    a={6.20,2.80,0.50};
    b={6.63,3.10,0.18};
    c={6.30,3.50,0.30};
    setNormalAndVertex(a,b,c);
    //g
    a={6.30,2.49,0.18};
    b={7.00,2.49,0.15};
    c={7.10,2.66,0.25};
    setNormalAndVertex(a,b,c);
    a={6.30,2.49,0.18};
    b={7.10,2.66,0.25};
    c={6.42,2.72,0.30};
    setNormalAndVertex(a,b,c);
    //h
    a={6.42,2.72,0.30};
    b={7.10,2.66,0.25};
    c={7.18,2.91,0.15};
    setNormalAndVertex(a,b,c);
    a={6.42,2.72,0.30};
    b={7.18,2.91,0.15};
    c={6.63,3.10,0.18};
    setNormalAndVertex(a,b,c);

  glEnd();
  // glava levo
  glBegin(GL_TRIANGLES);
    //a
    a={5.50,2.49,-0.60};
    b={5.90,2.03,-0.40 };
    c={6.10,2.38,-0.35 };
    setNormalAndVertex(a,b,c);

    a={5.50,2.49,-0.60};
    b={6.10,2.38,-0.35};
    c={5.70,2.91,-0.55};
    setNormalAndVertex(a,b,c);
    //b
    a={5.50,2.49,-0.60};
    b={5.70,2.91,-0.55};
    c={5.60,3.92,-0.35};
    setNormalAndVertex(a,b,c);

    a={5.50,2.49,-0.60};
    b={5.60,3.92,-0.35};
    c={4.80,3.92,-0.40};
    setNormalAndVertex(a,b,c);

    //c
    a={6.10,2.38,-0.35};
    b={6.20,2.80,-0.50};
    c={5.70,2.91,-0.55};
    setNormalAndVertex(a,b,c);
    //d
    a={5.70,2.91,-0.55};
    b={6.20,2.80,-0.50};
    c={6.30,3.50,-0.30};
    setNormalAndVertex(a,b,c);
    a={5.70,2.91,-0.55};
    b={6.30,3.50,-0.30};
    c={5.60,3.92,-0.35};
    setNormalAndVertex(a,b,c);
    //e
    a={6.10,2.38,-0.35};
    b={6.30,2.49,-0.18};
    c={6.42,2.72,-0.30};
    setNormalAndVertex(a,b,c);
    a={6.10,2.38,-0.35};
    b={6.42,2.72,-0.30};
    c={6.20,2.80,-0.50};
    setNormalAndVertex(a,b,c);
    //f
    a={6.20,2.80,-0.50};
    b={6.42,2.72,-0.30};
    c={6.63,3.10,-0.18};
    setNormalAndVertex(a,b,c);
    a={6.20,2.80,-0.50};
    b={6.63,3.10,-0.18};
    c={6.30,3.50,-0.30};
    setNormalAndVertex(a,b,c);
    //g
    a={6.30,2.49,-0.18};
    b={7.00,2.49,-0.15};
    c={7.10,2.66,-0.25};
    setNormalAndVertex(a,b,c);
    a={6.30,2.49,-0.18};
    b={7.10,2.66,-0.25};
    c={6.42,2.72,-0.30};
    setNormalAndVertex(a,b,c);
    //h
    a={6.42,2.72,-0.30};
    b={7.10,2.66,-0.25};
    c={7.18,2.91,-0.15};
    setNormalAndVertex(a,b,c);
    a={6.42,2.72,-0.30};
    b={7.18,2.91,-0.15};
    c={6.63,3.10,-0.18};
    setNormalAndVertex(a,b,c);

  glEnd();
  // glava top
  glBegin(GL_TRIANGLES);
    //b
    a={4.80,3.92,-0.40};
    b={4.80,3.92,0.40};
    c={5.60,3.92,0.35};
    setNormalAndVertex(a,b,c);

    a={4.80,3.92,-0.40};
    b={5.60,3.92,0.35};
    c={5.60,3.92,-0.35};
    setNormalAndVertex(a,b,c);
    //d
    a={5.60,3.92,-0.35};
    b={5.60,3.92,0.35};
    c={6.30,3.50,0.30};
    setNormalAndVertex(a,b,c);
    a={5.60,3.92,-0.35};
    b={6.30,3.50,0.30};
    c={6.30,3.50,-0.30};
    setNormalAndVertex(a,b,c);
    //f
    a={6.30,3.50,-0.30};
    b={6.30,3.50,0.30};
    c={6.63,3.10,0.18};
    setNormalAndVertex(a,b,c);
    a={6.30,3.50,0.30};
    b={6.63,3.10,0.18};
    c={6.63,3.10,-0.18};
    setNormalAndVertex(a,b,c);
    //h
    a={6.63,3.10,-0.18};
    b={6.63,3.10,0.18};
    c={7.18,2.91,0.15};
    setNormalAndVertex(a,b,c);
    a={6.63,3.10,-0.18};
    b={7.18,2.91,0.15};
    c={7.18,2.91,-0.15};
    setNormalAndVertex(a,b,c);
  glEnd();
  // zatvaramo glavu pozadi
  glBegin(GL_POLYGON);
    glVertex3f(4.80,3.92,0.40);
    glVertex3f(5.50,2.49,0.60);
    glVertex3f(5.90,2.03,0.40);
    glVertex3f(5.90,2.03,-0.40);
    glVertex3f(5.50,2.49,-0.60);
    glVertex3f(4.80,3.92,-0.40);
  glEnd();
  // zatvaramo nos
  glBegin(GL_POLYGON);
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




  glColor3f(1,1,0);
  glTranslatef(duzina/2,visina/2,0);
  glScalef(duzina,visina,sirina);
  glutWireCube(1);

}
