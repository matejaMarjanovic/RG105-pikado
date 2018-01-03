#define TIMER_INT 20

extern double horY, verX, horX, verY;
// extern double startDartX, startDartY, startDartZ;
extern double cameraX, cameraY, cameraZ;
extern int shootPhase, pickPhase1, pickPhase2;
extern double shootingSpotX, shootingSpotY, shootingSpotZ;
extern double animParam;
extern double lookX, lookY, lookZ;

void onTimer(int value);
void logicShootDart();
void logicResetValues();
void logicResetCamera();
void logicKeyPressed(unsigned char c);
