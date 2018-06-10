#include "lighting.hpp"
#include "game.hpp"
#include "camera.hpp"
#include <iostream>
#include <ctime>

#define TIMER_INT 20
#define MOVE_BACK 0
#define SHOOT 1

// standard callback functions for glut
void initialize();
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void onTimer(int val);

// will be used in onTimer function, the whole animation depends on it
double animationParameter = 0;

// window width and height, used in reshape callback function
int width, height;

// the main game object
Game game{
    Dartboard{
        DartboardCircle{5.7}, 
        15, 20}, 
    Dart{
        0, 0, -13, 
        0, 0.085, 2.7, 
        ShootingSpot{
            0, 0, 0
        }
    }
};
Camera cam{game};

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Darts");
    
    glutFullScreen();
    glutReshapeFunc(reshape);
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    
    initialize();
    
    glutMainLoop();
    return 0;
}

// lighting init 
void initialize() {
    srand(time(NULL));
    glClearColor(0.75, 0.75, 0.75, 0);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    ObjectLighting objLight{
        std::vector<GLfloat>{0.4, 0.4, 0.4, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        std::vector<GLfloat>{.8, .8, .8, 1},
        std::vector<GLfloat>{1, 1, 1, 0},
        GL_LIGHT0
    };
    objLight.setLighting();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, width/(double)height, 1, 50);
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cam.changeCam(game.dart());
    
    game.render();
    
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
    if(c == 27) {
        exit(EXIT_SUCCESS);
    }
    if(!game.m_startGame && c == ' ') {
        game.m_startGame = true;
        glutPostRedisplay();
    }
    if(game.m_startGame) {
        switch(c) {
            case 'g': // pick phase ends and shoot phase begins
                if(!game.m_shootPhase && cam.readyForFire()) {
                    animationParameter = 0;
                    game.m_pickPhase = false;
                    cam.m_pickPhase = false;
                    game.m_shootPhase = true;
                    cam.m_shootPhase = true;
                    cam.setCam();
                    glutTimerFunc(TIMER_INT, onTimer, SHOOT);
                }
                break;
            case 'p':
                if(game.m_pickPhase) {
                    game.dart().setShoot(game.shoot());
                    game.dart().setShootRotataion(); 
                    game.m_moveBack = true;
                    cam.m_moveBack = true;
                    glutTimerFunc(TIMER_INT, onTimer, MOVE_BACK);
                }
                break;
            case 'r': // reseting done the hard way
                // we reset all of the objects in game and the objects in those objects
                game.resetGame();
                cam.resetGame(game);
                // get the camera back to it's initial position
                cam.setCam();
                animationParameter = 0;
                glutPostRedisplay();
                break;
            // these are used for setting the shooting spot
            case 'w':
                if(game.m_pickPhase) {
                    game.goUp();
                    glutPostRedisplay();
                }
                break;
            case 'a':
                if(game.m_pickPhase) {
                    game.goLeft();
                    glutPostRedisplay();
                }
                break;
            case 's':
                if(game.m_pickPhase) {
                    game.goDown();
                    glutPostRedisplay();
                }
                break;
            case 'd':
                if(game.m_pickPhase) {
                    game.goRight();
                    glutPostRedisplay();
                }
                break;
            case ' ':
                if(game.m_pickPhase) {
                    game.increaseStrength();
                }
                break;
        }
    }
}

void onTimer(int value) {
    // when the player picks the shooting spot the camera goes back
    if(value == MOVE_BACK) {
        if(animationParameter <= 1) {
            cam.moveBack(animationParameter);
            animationParameter += 0.012;
            
            glutPostRedisplay();
            if(game.m_pickPhase) {
                glutTimerFunc(TIMER_INT, onTimer, MOVE_BACK);
            }
        }
        else {
            game.m_moveBack = false;
            cam.m_moveBack = false;
        }
    }
    // dart moving toward the shooting spot
    if(value == SHOOT) {
        if(animationParameter <= 1) {
            game.play(animationParameter);
            animationParameter += 0.027;
            
            glutPostRedisplay();
            if(game.m_shootPhase) {
                glutTimerFunc(TIMER_INT, onTimer, SHOOT);
            }
        }
        else {
            game.increaseValueSum();
        }
    }
}

// nothing special
void mouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_RIGHT_BUTTON:
            exit(EXIT_SUCCESS);
    }
}


