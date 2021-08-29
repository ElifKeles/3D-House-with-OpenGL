/* Elif Keleş - 161044033 */
/*     CSE461 - HW#1      */

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

/* variables for rotation */
int stopFlag = 1;
float myRotate[3] = { 0, 0, 0 };
int axis = -1;
float speed = 10.0;
int rotateX = -1, rotateY = -1;

/* variables for scaling */
float a = 0.6, b = 0.6, c = 0.6;

/* variables for translation */
float translateValueX = 0;
float translateValueY = 0;
int state;

/* keyboard handle function for special keys */
void myKeyboard(int button, int x, int y)
{
    switch (button)
    {        
        case GLUT_KEY_LEFT:
            if (state == GLUT_KEY_RIGHT)
                rotateY *= -1;
            axis = 1;            
            state = GLUT_KEY_LEFT;
            break;

        case GLUT_KEY_RIGHT: 
            if (state == GLUT_KEY_LEFT)
                rotateY *= -1;
            axis = 1;            
            state = GLUT_KEY_RIGHT;
            break;

        case GLUT_KEY_DOWN:
            if (state == GLUT_KEY_UP)
                rotateX *= -1;
            axis = 0;
            state = GLUT_KEY_DOWN;
            break;

        case GLUT_KEY_UP:
        axis = 0;
        if (state == GLUT_KEY_DOWN)
            rotateX *= -1;
        state = GLUT_KEY_UP;
        break;            
    }
    glutPostRedisplay();
}


/* keyboard handle function for ASCII characters*/
void handleKeypress(unsigned char key, int x, int y) {
    switch (key)
    {
    /* ESC or quit*/
    case 27: 
    case 'q':
        exit(0);
        break;
    
    /* stopping/ unstopping */
    case 's':
        stopFlag *= -1;
        break;

    /* translate to left */
    case 'l':
        if (stopFlag == -1)
        {
            translateValueX -= 0.2;
            glutPostRedisplay();
        }
        break;

    case 'r':
        if (stopFlag == -1)
        {
            translateValueX += 0.2;;
            glutPostRedisplay();
        }
        break;

    case 'u':
        if (stopFlag == -1)
        {
            translateValueY += 0.2;;
            glutPostRedisplay();
        }
        break;

    case 'd':
        if (stopFlag == -1)
        {
            translateValueY -= 0.2;;
            glutPostRedisplay();
        }
        break;

    case 'A':
        if (stopFlag == -1 && a < 0.975)
        {
            a += 0.01;
            b += 0.01;
            c += 0.01;
            glutPostRedisplay();
        }
        break;

    case 'a':
        if (stopFlag == -1 && a >= 0.2)
        {
            a -= 0.01;
            b -= 0.01;
            c -= 0.01;
            glutPostRedisplay();
        }
        break;
    }
}


void initRendering()
{
    glEnable(GL_COLOR_MATERIAL);
    /* Automatically normalize normals */
    glEnable(GL_NORMALIZE); 
    /* Enable smooth shading */
    glShadeModel(GL_SMOOTH);
}

/* Rotate function */
void rotateHouse() 
{
    if (stopFlag == 1) 
    {
        switch (axis)
        {
        case 0:
            myRotate[0] += (speed * rotateX);
            break;

        case 1:
            myRotate[1] += (speed * rotateY);
            break;
        }
    }
    glRotatef(myRotate[0], 1.0, 0.0, 0.0);
    glRotatef(myRotate[1], 0.0, 1.0, 0.0);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

/* function to draw the house */
void myHouse(void)
{
    /* initializing the background white */
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.5f, -2.0f);   
    glPushMatrix();
    glTranslatef(1.0f, 1.0f, 0.0f); 
    
    glScalef(a, b, c);  
    rotateHouse();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_POLYGON_OFFSET_FILL);

    /* door of the house */
    glBegin(GL_POLYGON);
    glColor3f(0.556863, 0.137255, 0.419608);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.45);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.25);
    glVertex3f(0.2 + translateValueX, 0.35 + translateValueY, 0.25);
    glVertex3f(0.2 + translateValueX, 0.35 + translateValueY, 0.45);
    glEnd();
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);

    /* front wall */
    glBegin(GL_POLYGON);
    glColor3f(0.258824, 0.435294, 0.258824);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.0);
    glEnd();

    /* back wall */
    glBegin(GL_POLYGON);
    glColor3f(0.258824, 0.435294, 0.258824);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.5);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.5);
    glEnd();

    /* left wall */
    glBegin(GL_POLYGON);
    glColor3f(0.560784, 0.737255, 0.560784);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.0);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.5);
    glEnd();
    
    /* right wall */
    glBegin(GL_POLYGON);
    glColor3f(0.560784, 0.737255, 0.560784);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.5);
    glEnd();

    /* base of the house */
    glBegin(GL_POLYGON);
    glColor3f(.20, 0.1, .2);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.0);
    glVertex3f(0.2 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.1 + translateValueY, 0.0);
    glEnd();

    /* left of roof */
    glColor3f(0.658824, 0.658824, 0.658824);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.8 + translateValueY, 0.25);
    glEnd();

    /* right of roof */
    glColor3f(0.658824, 0.658824, 0.658824);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.5);
    glVertex3f(0.2 + translateValueX, 0.8 + translateValueY, 0.25);
    glEnd();

    /* front roof */    
    glColor3f(0.329412, 0.329412, 0.329412);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.0);
    glVertex3f(0.9 + translateValueX, 0.8 + translateValueY, 0.25);
    glVertex3f(0.2 + translateValueX, 0.8 + translateValueY, 0.25);
    glEnd();

    /* back of the roof */
    glColor3f(0.329412, 0.329412, 0.329412);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + translateValueX, 0.575 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.575 + translateValueY, 0.5);
    glVertex3f(0.9 + translateValueX, 0.8 + translateValueY, 0.25);
    glVertex3f(0.2 + translateValueX, 0.8 + translateValueY, 0.25);
    glEnd();


    glDisable(GL_DEPTH_TEST);
    glPopMatrix();       
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    /* glut library initialization */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("My 3D House on OpenGL !");

    /* initializing the rendering */
    initRendering();
    /* draw the house */
    glutDisplayFunc(myHouse);
    /* keyboard */
    glutKeyboardFunc(handleKeypress);
    /* keyboard for specials */
    glutSpecialFunc(myKeyboard);
    
    glutReshapeFunc(handleResize);

    /* loop until q or ESC is pressed */
    glutMainLoop();
    /* terminate */
    return 0;
}