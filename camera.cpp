#include "camera.hpp"

// make the camera follow the dart
void Camera::changeCam(const Dart &dart) {
    if(!m_moveBack) {
        m_posX = dart.m_posX;
        m_posY = dart.m_posY;
        m_posZ = dart.m_posZ-4;
        setCam();
    }
}

// if the camera finished moving backwards
bool Camera::readyForFire() const {
    return m_posZ < -12.9;
}

// the main function for the camera class
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
            m_posX-0.25, m_posY+0.5, m_posZ,
            m_posX, m_posY, m_posZ+2,
            0, 1, 0
        );
    }
}

// camera moving backwards depending on the animation parameter
void Camera::moveBack(double animParam) {
    m_posZ = -5 + animParam*(-13+5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0, 0, m_posZ,
        0, 0, 0,
        0, 1, 0
    );
}

// reseting the game also needs reseting the camera to it's initial position
void Camera::resetGame(const Game& game) {
    m_pickPhase = game.m_pickPhase; 
    m_shootPhase = game.m_shootPhase;
    m_posX = game.m_dart.m_posX; 
    m_posY = game.m_dart.m_posY; 
    m_posZ = game.m_dart.m_posZ;
}
