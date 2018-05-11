#pragma once
#include "dart.hpp"
#include "game.hpp"

class Camera {
public:
    Camera(const Game &game)
        : m_pickPhase{game.m_pickPhase}, m_shootPhase{game.m_shootPhase},
          m_posX{game.m_dart.m_posX}, m_posY{game.m_dart.m_posY}, m_posZ{game.m_dart.m_posZ} { }
    void rotateCam(const double &angle);
    void changeCam(const Dart &dart);
    void setCam() const;
    bool m_pickPhase, m_shootPhase;
private:
    double m_posX, m_posY, m_posZ;
};
