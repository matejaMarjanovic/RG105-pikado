#ifndef _LOGIC_
#define _LOGIC_

#include "logic.h"

#endif

#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif
#include <stdio.h>
#include <time.h>

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

    return 0;
}


void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0, 1, 0);
    
    GLfloat specLight[] = {.7, .7, .7, 1};
    GLfloat specularMaterial[] = {.9, .9, .9, 1};
    GLfloat ambientMaterial[] = {.3, .3, .3, 1};
    diffuseMaterial[0] = .9;
    diffuseMaterial[1] = .9;
    diffuseMaterial[2] = .9;
    diffuseMaterial[3] = 1;
    
    
    glEnable(GL_LIGHTING);
    
    glDisable(GL_LIGHT1);
    // svetlo 1.
    GLfloat lightPos1[] = {-5, 15, 50, 1};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 80);
    
    drawEverything();
    
    glDisable(GL_LIGHT0);
//     svetlo 2.
    GLfloat lightPos2[] = {5, 15, 50, 1};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specLight);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    drawEverything();
    
    glutSwapBuffers();
}

void onKeyboard(unsigned char c, int mouseX, int mouseY) {
    logicKeyPressed(c);
}

void onTimer(int value) {
    if(value != 0) {
        return;
    }
    
    logicShootDart();
    
    glutPostRedisplay();
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

