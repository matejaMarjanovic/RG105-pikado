#define M_PI 3.1415
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// prilikom optimizacije iscrtavanja uveli smo ovu strukturu (da ne bismo racunali sinuse i kosinuse, vise od jednom)
typedef struct {
    double x, y;
}circle_coords;

extern double dartPosX1;
extern double dartPosX2;
extern double dartPosY1;
extern double dartPosY2;
extern double dartPosY3;
extern double dartPosZ1;
extern double dartPosZ2;
extern double dartPosZ3;

extern circle_coords pickCoord1, pickCoord2, pickCoord3, pickCoord4;

// globalne promenljive, zbog optimizacije iscrtavanja
extern int nBigCircle, nSmallCircle, nBigCircleParts;
extern circle_coords* trigBigCircle;
extern circle_coords* trigSmallCircle;

extern const double radius;
// ugao jednog od jednakih delova kruga za pikado
extern const double angle;

void drawEverything();

void drawDartsDarts();

void drawDartsCircle();
void drawDartsEverythingElse();
void drawDartsMachine();

// funkcija u kojoj se inicijalizuju vrednosti vektora i raznih promenljivih
void initializeTrigMatrix();
