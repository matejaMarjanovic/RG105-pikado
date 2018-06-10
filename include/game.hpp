#pragma once

#include "dartboard.hpp"
#include "dart.hpp"
#include "lighting.hpp"

class Camera;

// this is the main class which renders all objects and move them
class Game {
public:
    Game(const Dartboard &dartboard, const Dart &dart, bool pickPhase = true, bool shootPhase = false)
        : m_pickPhase{pickPhase}, m_shootPhase{shootPhase},
          m_dartboard{dartboard}, m_dart{dart},
          m_shoot{dart.m_shoot} { }
    void render() const;
    void play(double animParam);
    Dart& dart();
    void drawShootingSpot() const; 
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    ShootingSpot shoot() const;
    void resetGame();
    bool m_pickPhase, m_shootPhase, m_moveBack;
    friend class Camera;
private:
    Dartboard m_dartboard;
    Dart m_dart;
    ShootingSpot m_shoot;
};
