#include "dart.hpp"

void Dart::render() const {
    ObjectMaterial whiteMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.95, 0.95, 0.95, 1},
        std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
        120
    };
    
    glTranslatef(m_posX, m_posY, m_posZ);
    
    whiteMaterial.setLighting();
    glPushMatrix();
        glTranslatef(0, 0, 1.5*m_length);
        glutSolidCone(m_radius, m_length*0.4, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0, m_length);
        glBegin(GL_TRIANGLE_STRIP);
            for(double i = 0; i < 2*M_PI; i += M_PI/20) {
                glNormal3f(cos(i), sin(i), 0);
                glVertex3f(m_radius*cos(i), m_radius*sin(i), 0);
                
                glNormal3f(cos(i), sin(i), 0);
                glVertex3f(m_radius*cos(i), m_radius*sin(i), -m_length);
            }
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin(GL_POLYGON);
            glNormal3f(-1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.24);
            glVertex3f(0, 0.2, -0.14);
            glVertex3f(0, 0.2, 0.10);
        glEnd();
        
        glRotatef(120, 0, 0, 1);
        glBegin(GL_POLYGON);
            glNormal3f(-1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.24);
            glVertex3f(0, 0.2, -0.14);
            glVertex3f(0, 0.4, 0.10);
        glEnd();
        
        glRotatef(120, 0, 0, 1);
        glBegin(GL_POLYGON);
            glNormal3f(-1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.24);
            glVertex3f(0, 0.2, -0.14);
            glVertex3f(0, 0.2, 0.10);
        glEnd();
    glPopMatrix();
}

void Dart::move(double x, double y, double z){
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}

void Dart::setShoot(const ShootingSpot &shoot) {
    m_shoot.m_posX = shoot.m_posX;
    m_shoot.m_posY = shoot.m_posY;
    m_shoot.m_posZ = shoot.m_posZ;
}

double Dart::deltaX() const {
    return m_shoot.m_posX - m_startPosX;
}
double Dart::deltaY() const {
    return m_shoot.m_posY - m_startPosY;
}
double Dart::deltaZ() const {
    return m_shoot.m_posZ - m_startPosZ;
}
