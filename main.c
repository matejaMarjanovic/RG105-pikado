#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif
#include <stdio.h>

#define TIMER_INT 20

int firstFall = 1;
int shootPhase = 0, pickPhase = 1;
double shootingSpotX, shootingSpotY, shootingSpotZ = 10;
double moveDartX, moveDartY = 0.01, moveDartZ = 0.2;
double grav = 0.005;
double direction = 1, decDirection = 0.05;

void onTimer(int value);
void onDisplay();
void onKeyboard(unsigned char c, int x, int y);
void onReshape(int width, int height);

int main(int argc, char** argv) {
    initializeTrigMatrix(); // oslobodi prostor koje su zauzeli vektori
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 400);
    glutCreateWindow(argv[0]);
    
    glClearColor(0.25, 0, 0.25, 0);
    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);
    glutReshapeFunc(onReshape);
    
    glutMainLoop();
    free(trigBigCircle);
    free(trigSmallCircle);
    return 0;
}


void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(30, 0, 15, 0, 0, 0, 0, 1, 0);
    
    glPushMatrix();
        glTranslatef(0, 0, -10);
        drawDartsMachine();    
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(0, 0, 5);
        drawDartsDarts();
    glPopMatrix();
    
    glutSwapBuffers();
}

void onKeyboard(unsigned char c, int mouseX, int mouseY) {
    switch(c) {
        case 27:
            exit(EXIT_SUCCESS);
        case 'p':
        case 'P':
            if(pickPhase) { // u toku je biranje tacke u koju se gadja
                shootingSpotX = mouseX;
                shootingSpotY = mouseY;
                pickPhase = 0;
                shootPhase = 1; // sad moze da se gadja
            }
            break;
        case 's':
        case 'S':
            if(shootPhase) { // gadja se
                glutTimerFunc(TIMER_INT, onTimer, 0);
                break;
            }
    }
}

void onTimer(int value) {
    if(value != 0) {
        return;
    }
    
    dartPosX1 += moveDartX;
    dartPosX2 += moveDartX;
    
    dartPosY1 += moveDartY;
    dartPosY2 += moveDartY;
    dartPosY3 += moveDartY;
    
    dartPosZ1 -= moveDartZ;
    dartPosZ2 -= moveDartZ;
    dartPosZ3 -= moveDartZ;
        
    moveDartY += grav;
    
    if(dartPosY2 >= 9.5 && firstFall) { // samo jednom kreni da padas kada stignes/predjes odredjenu tacku
        grav *= -0.8;
        firstFall = 0;
    }
    
    glutPostRedisplay();
    
    if(dartPosZ3 <= -11.5) { // stigao do table
        shootPhase = 0;
    }
    
    if(shootPhase) { // ako i dalje leti nastavi da se pomeras
        glutTimerFunc(TIMER_INT, onTimer, 0);
    }
}

void onReshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, width/(double)height, 1, 500);
}

