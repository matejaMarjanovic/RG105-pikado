#include "game.hpp"

// calls the render functions of other objects 
// depending on the current state of the app
void Game::render() const {
    m_dartboard.render();
    if(m_pickPhase) {
        drawShootingSpot();
    }
    else if(m_shootPhase) {
        m_dart.render();
    }
}

// these functions move the shooting spot triangle
void Game::goUp() {
    m_shoot.m_posY += 0.035;
}
void Game::goDown() {
    m_shoot.m_posY -= 0.035;
}
void Game::goRight() {
    m_shoot.m_posX -= 0.035;
}
void Game::goLeft() {
    m_shoot.m_posX += 0.035;
}

// draws a yellow triangle whose top coordinates represent the potential shooting spot
void Game::drawShootingSpot() const {
    if(!m_moveBack) {
        ObjectMaterial yellowMaterial{
            std::vector<GLfloat>{0.05, 0.05, 0.05, 1},
            std::vector<GLfloat>{0.95, 0.45, 0.05, 1},
            std::vector<GLfloat>{0.6, 0.6, 0.6, 1},
            120
        };
        yellowMaterial.setLighting();
        glBegin(GL_TRIANGLES);
            glNormal3f(0, 0, -1);
            glVertex3f(m_shoot.m_posX, m_shoot.m_posY, -1.5);
            glVertex3f(m_shoot.m_posX-0.1, m_shoot.m_posY-0.2, -1.5);
            glVertex3f(m_shoot.m_posX+0.1, m_shoot.m_posY-0.2, -1.5);
        glEnd();
        }
}

// moves the dart on the line that represents the direction of the shooting spot
void Game::play(double animParam) {
    m_dart.move(
        m_dart.m_startPosX + animParam*1.42*m_dart.deltaX(),
        m_dart.m_startPosY + animParam*1.42*m_dart.deltaY(), 
        m_dart.m_startPosZ + animParam*m_dart.deltaZ()
    );
    m_dart.setAngle(animParam*180*2.3/M_PI);
}

// reseting the game
// calls resetGame for all of his objects 
void Game::resetGame() {
    m_pickPhase = true; 
    m_shootPhase = false;
    m_dartboard.resetGame();
    m_dart.resetGame();
    m_shoot.resetGame();
}

// some getters
ShootingSpot Game::shoot() const {
    return m_shoot;
}

Dart& Game::dart() {
    return m_dart;
}
