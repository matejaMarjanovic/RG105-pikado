#include "lighting.hpp"
#include "game.hpp"
#include <iostream>

void initialize();
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void onTimer(int val);

int animationParameter = 0;

double x, y, z;
int width, height;
Game game{Dartboard(DartboardCircle{5.7}, 15, 20), Dart{0, 0, -13, 2, 0.1, 2.1}};

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

void initialize() {
    glClearColor(0.75, 0.75, 0.75, 0);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    ObjectLighting objLight{
        std::vector<GLfloat>{0.1, 0.1, 0.1, 1},
        std::vector<GLfloat>{0.9, 0.9, 0.9, 1},
        std::vector<GLfloat>{1, 1, 1, 1},
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
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        -2, 0.5, -10,
        0, 0, 0,
        0, 1, 0
    );
    
    
    game.render();
    
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
    switch(c) {
        case 27:
            exit(EXIT_SUCCESS);
        case 'g':
            if(!animationParameter) {
                animationParameter = 1;
                glutTimerFunc(20, onTimer, 0);
            }
    }
}

void onTimer(int value) {
    game.play();
    
    glutPostRedisplay();
    if(animationParameter) {
        glutTimerFunc(20, onTimer, 0);
    }
}

void mouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_RIGHT_BUTTON:
            exit(EXIT_SUCCESS);
    }
}


