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
    
    srand(time(NULL));
    
    glutMainLoop();
    free(trigBigCircle);
    free(trigSmallCircle);
    return 0;
}


void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
    
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

