#pragma once
#include "dart.hpp"
#include "game.hpp"

// the camera class moves the camera (follows the dart or goes back when the shooting spot has been picked)
class Camera {
public:
    Camera(const Game &game)
        : m_pickPhase{game.m_pickPhase}, m_shootPhase{game.m_shootPhase},
          m_posX{game.m_dart.m_posX}, m_posY{game.m_dart.m_posY}, m_posZ{game.m_dart.m_posZ} {
              m_moveBack = false;
        }
    void rotateCam(const double &angle);
    void changeCam(const Dart &dart);
    void setCam() const;
    void resetGame(const Game& game);
    void moveBack(double animParam);
    bool readyForFire() const;
    bool m_pickPhase, m_shootPhase, m_moveBack;
private:
    double m_posX, m_posY, m_posZ;
};
