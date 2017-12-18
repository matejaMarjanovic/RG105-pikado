#ifndef _LOGIC_
#define _LOGIC_

#include "logic.h"

#endif

#ifndef _DRAWING_
#define _DRAWING_

#include "drawing.h"

#endif

// koordinate delova kruga u koje korisnik zeli da puca
circle_coords pickCoord1, pickCoord2, pickCoord3, pickCoord4;

// pocetne i krajnje tacke iglice
double dartPosX1 = 0, dartPosX2 = 0;
double dartPosY1 = 8, dartPosY2 = 7.75, dartPosY3 = 7.5;
double dartPosZ1 = 9, dartPosZ2 = 10.5, dartPosZ3 = 12;

double startDartX1 = 0, startDartX2 = 0;
double startDartY1 = 8, startDartY2 = 7.75, startDartY3 = 7.5;
double startDartZ1 = 9, startDartZ2 = 10.5, startDartZ3 = 12;


// globalne promenljive, zbog optimizacije iscrtavanja
int nBigCircle = 0, nSmallCircle = 0, nBigCircleParts = 0;
circle_coords* trigBigCircle;
circle_coords* trigSmallCircle;

const double radius = 7.5;
// ugao jednog od jednakih delova kruga za pikado
const double angle = M_PI/10;

void pickShootingSpot() {
    if(pickPhase == 0) {
        return;
    }
    double pickProduct = level*1.0/3;
    pickCoord1.x = radius*trigBigCircle[currentIndex].x*pickProduct; 
    pickCoord1.y = 7.5+radius*trigBigCircle[currentIndex].y*pickProduct;
    pickCoord2.x = radius*trigBigCircle[currentIndex].x*(pickProduct-1.0/3);
    pickCoord2.y = 7.5+radius*trigBigCircle[currentIndex].y*(pickProduct-1.0/3);
    pickCoord3.x = radius*trigBigCircle[(currentIndex+20)%400].x*(pickProduct-1.0/3);
    pickCoord3.y = 7.5+radius*trigBigCircle[(currentIndex+20)%400].y*(pickProduct-1.0/3);
    pickCoord4.x = radius*trigBigCircle[(currentIndex+20)%400].x*pickProduct;
    pickCoord4.y = 7.5+radius*trigBigCircle[(currentIndex+20)%400].y*pickProduct;
    
    glColor3f(.6, .6, .6);
    glBegin(GL_POLYGON);
        glVertex3f(pickCoord1.x, pickCoord1.y, 0.0003);
        glVertex3f(pickCoord2.x, pickCoord2.y, 0.0003);
        glVertex3f(pickCoord3.x, pickCoord3.y, 0.0003);
        glVertex3f(pickCoord4.x, pickCoord4.y, 0.0003);
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
    glColor3f(0, 1, 0); // krug u samom centru (manji)
    glBegin(GL_POLYGON);
        for(int i = 0; i < nSmallCircle; i++) {
            glVertex3f(radius/15*trigSmallCircle[i].x, 7.5 + radius/15*trigSmallCircle[i].y, 0.0001);
        }
    glEnd();
    
    glColor3f(1, 0, 0); // krug u samom centru (veci)
    glBegin(GL_POLYGON);
        for(int i = 0; i < nSmallCircle; i++) {
            glVertex3f(radius/25*trigSmallCircle[i].x, 7.5 + radius/25*trigSmallCircle[i].y, 0.0002);
        }
    glEnd();
    
    // najveci krug, crno-beli
    for(int j = 0; j < 20; j++) { // 20 delova kruga ima
        int color = j % 2;
        glColor3f(color, color, color);
        glBegin(GL_POLYGON);
            glVertex3f(0, 7.5, 0); // +1
            for(int i = 0; i < nBigCircleParts; i++) { // svaki ima 21 temena
                glVertex3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0);
            } 
        glEnd();
    }
    
    // crveno-zeleni prsten na krugu (srednji)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0)
                glColor3f(0, 1, 0);
        else
            glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glVertex3f(2*radius*trigBigCircle[j*20 + i].x/3, 7.5 + 2*radius*trigBigCircle[j*20 + i].y/3, 0.0001);
            } 
        glEnd();
    }
    
    // crveno-zeleni prsten na krugu (mali)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0)
            glColor3f(0, 1, 0);
        else
            glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glVertex3f(radius*trigBigCircle[j*20 + i].x/3, 7.5 + radius*trigBigCircle[j*20 + i].y/3, 0.0001);
            } 
        glEnd();
    }
    
    // crveno-zeleni prsten na krugu (veliki)
    for(int j = 0; j < 20; j++) {
        glLineWidth(2.5);
        if(j%2 == 0)
            glColor3f(0, 1, 0);
        else
            glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < nBigCircleParts; i++) {
                glVertex3f(radius*trigBigCircle[j*20 + i].x, 7.5 + radius*trigBigCircle[j*20 + i].y, 0.0001);
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
        glColor3f(0, 0, 0);
        glTranslatef(-1, 8, -10);
        glScalef(32, 35, 15);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix(); // iscrtaj belu zicanu kocku koja ce da bude preko crne
        glColor3f(1, 1, 1);
        glTranslatef(-1, 8, -10);
        glScalef(32, 35, 15);
        glutWireCube(1.01);
    glPopMatrix();
}

void drawDartsDarts() {
    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex3f(dartPosX1, dartPosY1, dartPosZ1);
        glColor3f(.7, .7, .7);
        glVertex3f(dartPosX2, dartPosY2, dartPosZ2);
    glEnd();
    
    glLineWidth(3);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(dartPosX1, dartPosY2, dartPosZ2);
        glVertex3f(dartPosX2, dartPosY3, dartPosZ3);
    glEnd();
}
