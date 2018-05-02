#include "dart.hpp"

void Dart::render() const {
    
    ObjectMaterial blueMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.15, 0.15, 0.85, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    blueMaterial.setLighting();
    
    glRotatef(75, 0, 1, 0);
    
    glPushMatrix();
        glTranslatef(m_posX, m_posY, 2.6 + m_posZ);
        glutSolidCone(0.15, 0.8, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(m_posX, m_posY, 1.3 + m_posZ);
        gluCylinder(gluNewQuadric(), 0.15, 0.15, 1.3, 30, 30);
    glPopMatrix();
}


void Dart::fly(double x, double y, double z){
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}
