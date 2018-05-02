#include "lighting.hpp"
#include "dartboard.hpp"
#include "dart.hpp"
#include <iostream>

void initialize();
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void onTimer(int val);

double x, y, z;
int width, height;

int main(int argc, char** argv) {
    x = 0;
    y = 0;
    z = -7;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Darts");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    
    initialize();
    
    glutMainLoop();
    return 0;
}

void onTimer(int val) {
    x += 0.05;
    y += 0.1;
    glutPostRedisplay();
    
    glutTimerFunc(20, onTimer, 0);
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
        0, 0, -10,
        0, 0, 0,
        0, 1, 0
    );
    
    Dartboard dartboard(DartboardCircle{5.7}, 15, 20);
    
    glPushMatrix();
        glRotatef(-10, 1, 0, 0);
        dartboard.render();
    glPopMatrix();
    
    Dart dart{x, y, z, 2};
    dart.render();
        
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
    switch(c) {
        case 27:
            exit(EXIT_SUCCESS);
        case 'g':
            glutTimerFunc(10, onTimer, 0);
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_RIGHT_BUTTON:
            exit(EXIT_SUCCESS);
    }
}

