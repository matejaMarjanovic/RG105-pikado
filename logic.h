#define TIMER_INT 20

extern double startDartX1, startDartX2;
extern double startDartY1, startDartY2, startDartY3;
extern double startDartZ1, startDartZ2, startDartZ3;
extern int level;
extern int currentIndex;
extern double cameraX, cameraY, cameraZ;
extern double moveCamera;
extern int firstFall;
extern int shootPhase, pickPhase;
extern double shootingSpotX, shootingSpotY, shootingSpotZ;
extern double moveDartX, moveDartY, moveDartZ;
extern double grav;
extern double direction, decDirection;
extern double constRotation;
extern double zAxisAcceleration;

void onTimer(int value);
void logicShootDart();
void logicResetValues();
void logicResetCamera();
void logicKeyPressed(unsigned char c);
