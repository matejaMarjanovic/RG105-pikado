#include "camera.hpp"

void Camera::changeCam(const Dart &dart) {
    m_posX = dart.m_posX;
    m_posY = dart.m_posY;
    m_posZ = dart.m_posZ-4;
    setCam();
}
void Camera::setCam() const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(m_pickPhase) {
        gluLookAt(
            0, 0, -5,
            0, 0, 0,
            0, 1, 0
        );
    }
    else if(m_shootPhase) {
        gluLookAt(
            m_posX, m_posY+0.5, m_posZ,
            m_posX, m_posY, m_posZ+2,
            0, 1, 0
        );
    }
}
