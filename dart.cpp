#include "dart.hpp"

void Dart::setShootRotataion() {
//     m_shootRot = skalarniProizvod(1, 2)/norma(1)*norma(2);
//     m_shootRot = (0, 0, m_posZ)o(m_shoot.m_posX - m_posX, m_shoot.m_posY - m_posY, m_shoot.m_posZ - m_posZ)
    m_shootRotationY = 
        180.0/M_PI*acos((
            (m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)
        ) /
        (
            sqrt((m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)) *
            sqrt(
                (m_shoot.m_posX - m_posX)*(m_shoot.m_posX - m_posX) + 
                (m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)
            )
        ));
    m_shootRotationX = 
        180.0/M_PI*acos((
            (m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)
        ) /
        (
            sqrt((m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)) *
            sqrt(
                (m_shoot.m_posY - m_posY)*(m_shoot.m_posY - m_posY) + 
                (m_shoot.m_posZ - m_posZ)*(m_shoot.m_posZ - m_posZ)
            )
        ));
    
    if(m_shoot.m_posY > m_posY) {
        m_shootRotationX *= -0.9;
        m_shoot.m_posY *= 0.88;
    }
    if(m_shoot.m_posX < m_posX) {
        m_shootRotationY *= -0.9;
        m_shoot.m_posX *= 0.88;
    }
}

void Dart::render() const {
    ObjectMaterial redMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.85, 0.1, 0.1, 1},
        std::vector<GLfloat>{0.7, 0.7, 0.7, 1},
        50
    };
    
    ObjectMaterial goldMaterial{
        std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
        std::vector<GLfloat>{0.95, 0.45, 0.05, 1},
        std::vector<GLfloat>{0.7, 0.7, 0.7, 1},
        50
    };
    
    glTranslatef(m_posX, m_posY, m_posZ);
    glRotatef(m_shootRotationX, 1, 0, 0);
    glRotatef(m_shootRotationY, 0, 1, 0);
    
    goldMaterial.setLighting();
    glPushMatrix();
        
        glTranslatef(0, 0, m_length);
        glRotatef(m_angle, 0, 0, 1);
        glutSolidCone(m_radius, m_length*0.4, 40, 40);
    glPopMatrix();
    
    redMaterial.setLighting();
    glPushMatrix();
        
        glTranslatef(0, 0, m_length);
        glRotatef(m_angle, 0, 0, 1);
        glBegin(GL_TRIANGLE_STRIP);
            for(double i = 0; i < 2*M_PI; i += M_PI/20) {
                glNormal3f(cos(i), sin(i), 0);
                glVertex3f(m_radius*cos(i), m_radius*sin(i), 0);
                
                glNormal3f(cos(i), sin(i), 0);
                glVertex3f(m_radius*cos(i), m_radius*sin(i), -m_length);
            }
            glVertex3f(m_radius*cos(0), m_radius*sin(0), 0);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        
        glTranslatef(0, 0, 0.35);
        glRotatef(m_angle, 0, 0, 1);
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.35);
            glVertex3f(0, 0.25, -0.60);
            glVertex3f(0, 0.25, -0.25);
            glVertex3f(0, 0, 0);
        glEnd();
        
        glRotatef(120, 0, 0, 1);
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.35);
            glVertex3f(0, 0.25, -0.60);
            glVertex3f(0, 0.25, -0.25);
            glVertex3f(0, 0, 0);
        glEnd();
        
        glRotatef(120, 0, 0, 1);
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -0.35);
            glVertex3f(0, 0.25, -0.60);
            glVertex3f(0, 0.25, -0.25);
            glVertex3f(0, 0, 0);
        glEnd();
    glPopMatrix();
}

void Dart::setAngle(const double &angle) {
    m_angle = angle;
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
