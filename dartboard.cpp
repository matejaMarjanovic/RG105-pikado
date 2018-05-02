#include "dartboard.hpp"

void Dartboard::render(void) const {
    ObjectMaterial dartboardMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.15, 0.15, 1},
        std::vector<GLfloat>{1, 1, 1, 1},
        30
    };
    dartboardMaterial.setLighting();
    
    glPushMatrix();
        glScalef(m_width, m_height, 2.5);
        glutSolidCube(1);
    glPopMatrix();
    
    m_dartCirc.render();
}

void DartboardCircle::render() const {
    glPushMatrix();
        glScalef(m_radius, m_radius, 1.0001);
        drawBigCircle();
        drawLineCircle1();
        drawLineCircle2();
        drawCentralCirlces();
    glPopMatrix();
}

void DartboardCircle::drawCentralCirlces() const {
    ObjectMaterial redMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.85, 0.15, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    ObjectMaterial greenMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.85, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };

    greenMaterial.setLighting();
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(0, 0, 0);
        for(double angle = 0; angle <= 2*M_PI; angle += M_PI/20) {
            glVertex3f(0.085*cos(angle), 0.085*sin(angle), 0);
        }
        glVertex3f(0, 0, 0);
    glEnd();
    
    redMaterial.setLighting();
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(0, 0, 0);
        for(double angle = 0; angle <= 2*M_PI; angle += M_PI/20) {
            glVertex3f(0.0425*cos(angle), 0.0425*sin(angle), 0);
        }
        glVertex3f(0, 0, 0);
    glEnd();
}

void DartboardCircle::drawBigCircle() const {
    ObjectMaterial blackMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.15, 0.15, 1},
        std::vector<GLfloat>{0.5, 0.5, 0.5, 1},
        120
    };
    ObjectMaterial whiteMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.85, 0.85, 0.85, 1},
        std::vector<GLfloat>{0.5, 0.5, 0.5, 1},
        120
    };
    
    for(int i = 0; i < 20; i++) {
        i % 2 ? whiteMaterial.setLighting() : blackMaterial.setLighting();
        glBegin(GL_POLYGON);
            glNormal3f(0, 0, -1);
            glVertex3f(0, 0, 0);
            for(double angle = -M_PI/20 + i*M_PI/10; angle <= M_PI/20 + i*M_PI/10; angle += M_PI/480) {
                glVertex3f(cos(angle), sin(angle), 0);
            }
            glVertex3f(0, 0, 0);
        glEnd();   
    }
}

void DartboardCircle::drawLineCircle1() const {
    ObjectMaterial redMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.85, 0.15, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    ObjectMaterial greenMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.85, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    
    for(int i = 0; i < 20; i++) {
        i % 2 ? greenMaterial.setLighting() : redMaterial.setLighting();
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(0, 0, -1);
            for(double angle = -M_PI/20 + i*M_PI/10; angle <= M_PI/20 + i*M_PI/10; angle += M_PI/140) {
                glVertex3f(0.56*cos(angle), 0.56*sin(angle), 0);
                glVertex3f(0.63*cos(angle), 0.63*sin(angle), 0);
            }
        glEnd();   
    }
}

void DartboardCircle::drawLineCircle2() const {
    ObjectMaterial redMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.85, 0.15, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    ObjectMaterial greenMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.85, 0.15, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    
    for(int i = 0; i <= 20; i++) {
        i % 2 ? greenMaterial.setLighting() : redMaterial.setLighting();
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(0, 0, -1);
            for(double angle = -M_PI/20 + i*M_PI/10; angle < M_PI/20 + i*M_PI/10; angle += M_PI/140) {
                glVertex3f(cos(angle), sin(angle), 0);
                glVertex3f(0.93*cos(angle), 0.93*sin(angle), 0);
            }
        glEnd();   
    }
}



