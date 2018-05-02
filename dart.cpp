#include "dart.hpp"

void Dart::render() const {
    
    ObjectMaterial blueMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.15, 0.85, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    
    ObjectMaterial goldMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.9, 0.6, 0.1, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    
    
    glRotatef(15, 1, 0, 0);
    glTranslatef(m_posX, m_posY, m_posZ);
    
    glPushMatrix();
        goldMaterial.setLighting();
        glTranslatef(0, 0, 1.5*m_length);
        glutSolidCone(m_radius, m_length*0.4, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
        blueMaterial.setLighting();
        glTranslatef(0, 0, m_length);
        gluCylinder(gluNewQuadric(), m_radius, m_radius, m_length*0.6, 30, 30);
    glPopMatrix();
}

void Dart::move(double x, double y, double z){
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}

double Dart::posX() const {
    return m_posX;
}
double Dart::posY() const {
    return m_posY;
}
double Dart::posZ() const {
    return m_posZ;
}
