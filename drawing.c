#ifndef _LOGIC_
#define _LOGIC_

#include "logic.h"

#endif

#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif

// pocetne koordinate strelice
double dartPosX = 0, dartPosY = 7.1, dartPosZ = 10.5;


// globalne promenljive, zbog optimizacije iscrtavanja
int nBigCircle = 0, nSmallCircle = 0, nBigCircleParts = 0;
circle_coords* trigBigCircle;
circle_coords* trigSmallCircle;

const double radius = 7.5;
// ugao jednog od jednakih delova kruga za pikado
const double angle = M_PI/10;

void pickShootingSpot() {
    if(pickPhase1 == 0 && pickPhase2 == 0) {
        return;
    }
    // horizontalna linija
    glDisable(GL_LIGHTING);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(-horX, horY, 0.05);
        glVertex3f(horX, horY, 0.05);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex3f(verX, -verY, .1);
        glVertex3f(verX, verY, .1);
    glEnd();
}

void drawEverything() {
    glPushMatrix();
        glTranslatef(0, 0, -15);
        drawDartsMachine();    
        pickShootingSpot();
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(0, 0, 5);
        drawDartsDarts();
    glPopMatrix();
}

void initializeTrigMatrix() {
    int k = 0;
    trigSmallCircle = malloc(640*sizeof(circle_coords)); // vrednosti sinusa i kosinusa za male krugove u centru
    for(double i = 0; i < 2*M_PI; i += M_PI/320) {
        trigSmallCircle[k].x = cos(i);
        trigSmallCircle[k++].y = sin(i);
    }
    nSmallCircle = k;
    
    k = 0;
    trigBigCircle = malloc(800*sizeof(circle_coords)); // vrenosti sinusa i kosinusa za veliki krug
    for(double i = -M_PI/20; i < 2*M_PI - M_PI/20; i += angle/20) {
        trigBigCircle[k].x = cos(i);
        trigBigCircle[k].y = sin(i);
        k++;
    } 
    
    nBigCircle = k;
    nBigCircleParts = 20;
    
    
}

void drawDartsCircle() {
    diffuseMaterial[0] = 0;
    diffuseMaterial[1] = 1;
    diffuseMaterial[2] = 0;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glBegin(GL_POLYGON);
        for(int i = 0; i < nSmallCircle; i++) {
            glNormal3f(radius/15*trigSmallCircle[i].x, 7.5 + radius/15*trigSmallCircle[i].y, 0.0001);
            glVertex3f(radius/15*trigSmallCircle[i].x, 7.5 + radius/15*trigSmallCircle[i].y, 0.0001);
        }
    glEnd();
    
    diffuseMaterial[0] = 1;
    diffuseMaterial[1] = 0;
    diffuseMaterial[2] = 0;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glBegin(GL_POLYGON);
        for(int i = 0; i < nSmallCircle; i++) {
            glNormal3f(radius/25*trigSmallCircle[i].x, 7.5 + radius/25*trigSmallCircle[i].y, 0.0002);
            glVertex3f(radius/25*trigSmallCircle[i].x, 7.5 + radius/25*trigSmallCircle[i].y, 0.0002);
        }
    glEnd();
    
    // najveci krug, crno-beli
    for(int j = 0; j < 20; j++) { // 20 delova kruga ima
        int color = j % 2;
        diffuseMaterial[0] = color;
        diffuseMaterial[1] = color;
        diffuseMaterial[2] = color;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        glBegin(GL_POLYGON);
            glNormal3f(0, 7.5, 0);
            glVertex3f(0, 7.5, 0); // +1
            for(int i = 0; i < nBigCircleParts; i++) { // svaki ima 21 temena
                glNormal3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0);
                glVertex3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0);
            } 
        glEnd();
    }
    
    glLineWidth(5);
    // crveno-zeleni prsten na krugu (srednji)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0) {
            diffuseMaterial[0] = 0;
            diffuseMaterial[1] = 1;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        else {
            diffuseMaterial[0] = 1;
            diffuseMaterial[1] = 0;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        glBegin(GL_TRIANGLE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glNormal3f(2*radius*trigBigCircle[j*20 + i].x/3, 7.5 + 2*radius*trigBigCircle[j*20 + i].y/3, 0.0001);
                glVertex3f(2*radius*trigBigCircle[j*20 + i].x/3, 7.5 + 2*radius*trigBigCircle[j*20 + i].y/3, 0.0001);
                
                glNormal3f(15*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 15*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
                glVertex3f(15*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 15*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
            } 
        glEnd();
    }
    
    // crveno-zeleni prsten na krugu (mali)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0) {
            diffuseMaterial[0] = 0;
            diffuseMaterial[1] = 1;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        else {
            diffuseMaterial[0] = 1;
            diffuseMaterial[1] = 0;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        glBegin(GL_TRIANGLE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glNormal3f(radius*trigBigCircle[j*20 + i].x/3, 7.5 + radius*trigBigCircle[j*20 + i].y/3, 0.0001);
                glVertex3f(radius*trigBigCircle[j*20 + i].x/3, 7.5 + radius*trigBigCircle[j*20 + i].y/3, 0.0001);
                
                glNormal3f(7.2*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 7.2*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
                glVertex3f(7.2*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 7.2*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
            } 
        glEnd();
    }
    
    // crveno-zeleni prsten na krugu (veliki)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0) {
            diffuseMaterial[0] = 0;
            diffuseMaterial[1] = 1;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        else {
            diffuseMaterial[0] = 1;
            diffuseMaterial[1] = 0;
            diffuseMaterial[2] = 0;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        }
        glBegin(GL_TRIANGLE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glNormal3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0.0001);
                glVertex3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0.0001);
                
                glNormal3f(23*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 23*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
                glVertex3f(23*radius*trigBigCircle[j*20 + i].x/24, 7.5 + 23*radius*trigBigCircle[j*20 + i].y/24, 0.0001);
            } 
        glEnd();
    }
}

void drawDartsMachine() {
    drawDartsCircle();
    drawDartsEverythingElse();
}

void drawDartsEverythingElse() {
    glPushMatrix(); // iscrtaj crnu kocku i izvrsi transformacije
        diffuseMaterial[0] = 0;
        diffuseMaterial[1] = 0;
        diffuseMaterial[2] = 0;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        
        glTranslatef(-1, 8, -9);
        glScalef(32, 35, 15);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix(); // iscrtaj belu zicanu kocku koja ce da bude preko crne
        diffuseMaterial[0] = 1;
        diffuseMaterial[1] = 1;
        diffuseMaterial[2] = 1;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        glTranslatef(-1, 8, -9);
        glScalef(32, 35, 15);
        glutWireCube(1.01);
    glPopMatrix();
}

void drawDartsDarts() {
    glLineWidth(1);
    diffuseMaterial[0] = .8;
    diffuseMaterial[1] = .8;
    diffuseMaterial[2] = .2;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    
    glPushMatrix();
        glRotatef(animParam*2*M_PI/3 - M_PI/3, 1, 0, 0);
        glTranslatef(dartPosX, dartPosY, dartPosZ);
        glRotatef(180, 0, 1, 0);
        glutSolidCone(0.1, 1.6, 10, 10);
    glPopMatrix();
}
