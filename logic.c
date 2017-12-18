#ifndef _LOGIC_
#define _LOGIC_

#include "logic.h"

#endif

#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif

#include <time.h>

int level = 3;
int currentIndex = 0;
double zAxisAcceleration = 1.03;
double cameraX = 0, cameraY = 0, cameraZ = 4;
double moveCamera = 0.1;
int firstFall = 1;
int shootPhase = 0, pickPhase = 1;
double shootingSpotX, shootingSpotY, shootingSpotZ = -10;
double moveDartX, moveDartY = 0.08, moveDartZ = 0.35;
double grav = 0.01;
double direction = 1, decDirection = 0.05;
double constRotation = 1/70.0;

void logicKeyPressed(unsigned char c) {
    switch(c) {
        case 27:
            exit(EXIT_SUCCESS);
        
        case 'p':
        case 'P':
            if(pickPhase) { // u toku je biranje tacke u koju se gadja
                logicResetValues();
                pickPhase = 0;
                shootPhase = 1; // sad moze da se gadja
                glutPostRedisplay();
            }
            break;
        case 'f':
        case 'F':
            if(shootPhase) { // gadja se
                cameraX = 20;
                cameraZ = 4;
                glutTimerFunc(TIMER_INT, onTimer, 0);
            }
            break;
        case 'a':
        case 'A':
            if(pickPhase) {
                currentIndex += 20;
                currentIndex %= 400;
                glutPostRedisplay();
            }
            else {
                cameraZ += moveCamera;
                glutPostRedisplay();
            }
            
            break;
        case 'd':
        case 'D':
            if(pickPhase) {
                currentIndex -= 20;
                if(currentIndex < 0) {
                    currentIndex += 400;
                }
                glutPostRedisplay();
            }
            else {
                cameraZ -= moveCamera;
                glutPostRedisplay();
            }
            break;
        case 'w':
        case 'W':
            if(pickPhase) {
                if(level < 3) {
                    level += 1;
                }
                glutPostRedisplay();
            }
            else {
                cameraX += moveCamera;
                glutPostRedisplay();
            }
            break;
        case 's':
        case 'S':
            if(pickPhase) {
                if(level > 1) {
                    level -= 1;
                }
                glutPostRedisplay();
            }
            else {
                cameraX -= moveCamera;
                glutPostRedisplay();
            }
            break;
        case 'i':
        case 'I':
            cameraX *= 0.9;
            cameraY *= 0.9;
            cameraZ *= 0.9;
            glutPostRedisplay();
            
            break;
        case 'o':
        case 'O':
            cameraX *= 10/9.0;
            cameraY *= 10/9.0;
            cameraZ *= 10/9.0;
            glutPostRedisplay();
            
            break;
        case 'R':
        case 'r':
            if(!pickPhase && !shootPhase) {
                logicResetValues();
                logicResetCamera();
                glutPostRedisplay();
            }
            break;
    }
}

void logicShootDart() {
    
    dartPosX1 += moveDartX;
    dartPosX2 += moveDartX;
    
    dartPosY1 += moveDartY - constRotation;
    dartPosY2 += moveDartY;
    dartPosY3 += moveDartY + constRotation;

    dartPosZ1 -= moveDartZ;
    dartPosZ2 -= moveDartZ;
    dartPosZ3 -= moveDartZ;
        
    moveDartY += grav; // prvo se ide gore, a negde od sredine krece
    moveDartZ *= zAxisAcceleration; // ubrzavaj vremenom
        
    if((dartPosY3 >= dartPosY1) && firstFall) { // samo jednom kreni da padas kada stignes/predjes odredjenu tacku
        grav *= -1;
        firstFall = 0;
    }
    
    glutPostRedisplay();
    
    if(dartPosZ3 <= -16) { // stigao do table
        shootPhase = 0;
    }
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

void logicResetValues() {
    double pickX1 = max(pickCoord1.x, pickCoord2.x);
    pickX1 = max(pickX1, pickCoord3.x);
    pickX1 = max(pickX1, pickCoord4.x);
    
    double pickX2 = min(pickCoord1.x, pickCoord2.x);
    pickX2 = min(pickX2, pickCoord3.x);
    pickX2 = min(pickX2, pickCoord4.x);
    
    double pickY1 = max(pickCoord1.y, pickCoord2.y);
    pickY1 = max(pickY1, pickCoord3.y);
    pickY1 = max(pickY1, pickCoord4.y);
    
    double pickY2 = min(pickCoord1.y, pickCoord2.y);
    pickY2 = min(pickY2, pickCoord3.y);
    pickY2 = min(pickY2, pickCoord4.y);
    
    shootingSpotX = pickX2 + (pickX1-pickX2)*((double)rand()/RAND_MAX);
    shootingSpotY = pickY2 + (pickY1-pickY2)*((double)rand()/RAND_MAX);
    
    moveDartX = (-startDartX1 + shootingSpotX)/(19/0.35);
    moveDartY = (-startDartY1 + shootingSpotY)/(19/0.35);
    
    pickPhase = 1;
    dartPosX1 = 0; dartPosX2 = 0;
    dartPosY1 = 8; dartPosY2 = 7.75; dartPosY3 = 7.5;
    dartPosZ1 = 9; dartPosZ2 = 10.5; dartPosZ3 = 12;
    moveDartZ = 0.35;
    grav = 0.002;
    direction = 1; decDirection = 0.05;
    constRotation = 1/70.0;
    firstFall = 1;
}

void logicResetCamera() {
    cameraX = 0;
    cameraY = 0;
    cameraZ = 5;
}

