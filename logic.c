#ifndef _LOGIC_
#define _LOGIC_

#include "logic.h"

#endif

#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif

#include <time.h>

#define FIRST_PERSON 0
#define THIRD_PERSON 1

int cameraOption = FIRST_PERSON;
double animParam = 0;
double verX = 0, horY = 7.5, horX = 60, verY = 60;
double cameraX = 0, cameraY = 5, cameraZ = -7;
double lookX = 0, lookY = 5, lookZ = -11;
int shootPhase = 0, pickPhase1 = 1, pickPhase2 = 0;
double shootingSpotX, shootingSpotY, shootingSpotZ = -18.5;
const double startDartX = 0, startDartY = 7.5, startDartZ = 10.5;

void logicKeyPressed(unsigned char c) {
    switch(c) {
        case 27:
            free(trigBigCircle);
            free(trigSmallCircle);
            exit(EXIT_SUCCESS);
        
        case 'p':
        case 'P':
            if(pickPhase2) { // u toku je biranje tacke u koju se gadja
                pickPhase2 = 0;
                verY = 0;
                horX = 0;
                shootPhase = 1; // sad moze da se gadja
                cameraX = lookX = dartPosX;
                cameraY = lookY = dartPosY;
                lookZ = dartPosZ;
                cameraZ = lookZ + 5;
                glutPostRedisplay();
            }
            if(pickPhase1) {
                pickPhase1 = 0;
                pickPhase2 = 1;
                glutPostRedisplay();
            }
            break;
        case 'f':
        case 'F':
            if(shootPhase) { // gadja se
                shootingSpotY = horY;
                shootingSpotX = verX;
                glutTimerFunc(TIMER_INT, onTimer, 0);
            }
            break;
        case 'a':
        case 'A':
            if(pickPhase1) {
                verX -= 0.1;
                glutPostRedisplay();
            }
            
            break;
        case 'd':
        case 'D':
            if(pickPhase1) {
                verX += 0.1;
                glutPostRedisplay();
            }
            break;
        case 'w':
        case 'W':
            if(pickPhase2) {
                horY += 0.1;
                glutPostRedisplay();
            }
            break;
        case 's':
        case 'S':
            if(pickPhase2) {
                horY -= 0.1;
                glutPostRedisplay();
            }
            break;
        case 'R':
        case 'r':
            if(!shootPhase && !pickPhase1 && !pickPhase2) {
                logicResetValues();
                logicResetCamera();
                glutPostRedisplay();
            }
            break;
        case 'c':
        case 'C':
            if(cameraOption == FIRST_PERSON) {
                cameraOption = THIRD_PERSON;
            }
            else {
                cameraOption = FIRST_PERSON;
            }
            glutPostRedisplay();
            break;
    }
}

void logicShootDart() {
    if(!shootPhase) {
        return;
    }
    
    if(cameraOption == FIRST_PERSON) {
        lookX = dartPosX;
        lookY = dartPosY;
        lookZ = dartPosZ;
        cameraX = lookX;
        cameraY = lookY;
        cameraZ = lookZ + 5;
    }
    else {
        cameraX = 5;
        cameraY = 30;
        cameraZ = -5;
        lookX = lookZ = 0;
        lookY = 7.5;
    }
        
    dartPosX = startDartX + animParam*(shootingSpotX - startDartX);
    dartPosY = startDartY + animParam*(shootingSpotY - startDartY);
    dartPosZ = startDartZ + animParam*(shootingSpotZ - startDartZ);
    
    if(animParam >= 1) { // stigao do table
        shootPhase = 0;
    }
    
    animParam += 0.02;
}

void logicResetValues() {
    horX = 60;
    verY = 60;
    
    pickPhase1 = 1;
    pickPhase2 = 0;
    shootPhase = 0;
    
    dartPosX = startDartX; 
    dartPosY = startDartY;
    dartPosZ = startDartZ;
    animParam = 0;
}

void logicResetCamera() {
    cameraX = 0;
    cameraY = 5;
    cameraZ = -7;
    
    lookX = 0;
    lookY = 5;
    lookZ = -11;
}

