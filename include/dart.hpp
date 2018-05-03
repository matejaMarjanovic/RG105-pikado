#pragma once

#include "lighting.hpp"
#include <cmath>

class Dart {
public:
    Dart(const double &posX, const double &posY, const double &posZ, const double &speed, const double &radius, const double &length)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ}, 
          m_speed{speed},
          m_radius{radius}, m_length{length} { }
    void render() const;
    void move(double x, double y, double z);
    double posX() const;
    double posY() const;
    double posZ() const;
private:
    double m_posX, m_posY, m_posZ;
    double m_speed;
    double m_radius, m_length;
};
