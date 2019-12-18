#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
//#include "image.h"

static int window_width;
static int window_height;


/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Wolf Quest");

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}



static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 15);
}


static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    gluLookAt(2, 5, 10, 0, 0, 0, 0, 1, 0);


    glColor3f(0.96, 0.96, 0.96);
    glBegin(GL_LINES);
        glVertex3d(0,0, 0);
        glVertex3d(7,0,0);
        glVertex3d(0,0, 0);
        glVertex3d(0,7,0);
        glVertex3d(0,0, 0);
        glVertex3d(0,0,7);
    glEnd();

	glColor3f(1,0,0);
	glutSolidSphere(1, 32, 32);
    glutSwapBuffers();
}
