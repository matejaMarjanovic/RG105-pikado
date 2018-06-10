#include "dartboard.hpp"

// renders the dartboard
// a black cube and a circle
void Dartboard::render(void) const {
    ObjectMaterial dartboardMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.15, 0.15, 1},
        std::vector<GLfloat>{1, 1, 1, 1},
        30
    };
    dartboardMaterial.setLighting();
    
    glPushMatrix();        
        glPushMatrix();
            glScalef(m_width, m_height, 2.5);
            glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
            m_dartCirc.render();
        glPopMatrix();

    glPopMatrix();
}

// renders a circle that is constructed of a few layers
void DartboardCircle::render() const {
    glScalef(m_radius, m_radius, 1);
    drawNumericValues();
    drawBigCircle();
    drawLineCircle1();
    drawLineCircle2();
    drawCentralCirlces();
}

void DartboardCircle::drawNumericValues() const {
    std::string strings[] = {"11", "14", "9", "12", "5", "20", "1", "18", "4", "13", "6", "10", "5", "2", "17", "3", "19", "7", "16", "8"};
    
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    for(int i = 0; i < 20; ++i) {
        std::string str(strings[i]);
        glRasterPos3f(1.3*cos(i*M_PI/10.0), 1.3*sin(i*M_PI/10.0), 1);

        for (auto c : str) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }
    glEnable(GL_LIGHTING);
}

// these functions are the "layers" for the dartboard circle
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
            for(double angle = -M_PI/19.999999 + i*M_PI/10; angle <= M_PI/19.999999 + i*M_PI/10; angle += M_PI/140) {
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
            for(double angle = -M_PI/19.999999 + i*M_PI/10; angle <= M_PI/19.999999 + i*M_PI/10; angle += M_PI/140) {
                glVertex3f(0.57*cos(angle), 0.57*sin(angle), 0);
                glVertex3f(0.62*cos(angle), 0.62*sin(angle), 0);
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
            for(double angle = -M_PI/19.999999 + i*M_PI/10; angle < M_PI/19.999999 + i*M_PI/10; angle += M_PI/140) {
                glVertex3f(cos(angle), sin(angle), 0);
                glVertex3f(0.95*cos(angle), 0.95*sin(angle), 0);
            }
        glEnd();   
    }
}

// reseting to initial values
void Dartboard::resetGame() {
    m_dartCirc.resetGame();
    m_width = 15; 
    m_height = 20;
}

void DartboardCircle::resetGame() {
    m_radius = 5.7;
}


