#pragma once

#include "lighting.hpp"
#include <cmath>
#include <iostream>

class Game;
class Camera;
class ShootingSpot;
class Dart;

class ShootingSpot {
public:
    ShootingSpot(double posX, double posY, double posZ)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ} { }
    friend class Dart;
    friend class Game;
private:
    double m_posX, m_posY, m_posZ;
};

class Dart {
public:
    Dart(const double &posX, const double &posY, const double &posZ, const double &speed, 
         const double &radius, const double &length, const ShootingSpot &shoot)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ}, m_speed{speed},
          m_radius{radius}, m_length{length}, m_shoot{shoot},
          m_startPosX{posX}, m_startPosY{posY}, m_startPosZ{posZ} { }
    void render() const;
    void move(double x, double y, double z);
    double deltaX() const;
    double deltaY() const;
    double deltaZ() const;
    void setShoot(const ShootingSpot &shoot);
    friend class Camera;
    friend class Game;
private:
    double m_posX, m_posY, m_posZ;
    double m_speed, m_radius, m_length;
    ShootingSpot m_shoot;
    double m_startPosX, m_startPosY, m_startPosZ;
};
