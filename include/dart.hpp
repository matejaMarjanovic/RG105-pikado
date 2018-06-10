#pragma once

#include "lighting.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>

class Game;
class Camera;
class ShootingSpot;
class Dart;

// this class is used to save the shooting spot the player has picked
class ShootingSpot {
public:
    ShootingSpot(double posX, double posY, double posZ)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ} { }
    void resetGame();
    void calculateValue(double radius);
    friend class Dart;
    friend class Game;
private:
    double m_posX, m_posY, m_posZ;
    int m_value;
};

// this class is responsible for rendering, moving, rotating... the dart
class Dart {
public:
    Dart(const double &posX, const double &posY, const double &posZ, const double &strength, 
         const double &radius, const double &length, const ShootingSpot &shoot, const double &angle = 0)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ}, m_strength{strength},
          m_radius{radius}, m_length{length}, m_shoot{shoot},
          m_startPosX{posX}, m_startPosY{posY}, m_startPosZ{posZ} { }
    void render() const;
    void move(double x, double y, double z);
    double deltaX() const;
    double deltaY() const;
    double deltaZ() const;
    void increaseStrength();
    void setShoot(const ShootingSpot &shoot);
    void setAngle(const double &angle);
    void setShootRotataion();
    void resetGame();
    friend class Camera;
    friend class Game;
private:
    double m_posX, m_posY, m_posZ;
    double m_strength, m_radius, m_length;
    ShootingSpot m_shoot;
    double m_startPosX, m_startPosY, m_startPosZ;
    double m_angle;
    double m_shootRotationX, m_shootRotationY;
};
