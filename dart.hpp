#pragma once

#include "lighting.hpp"
#include <cmath>

class Dart {
public:
    Dart(const double &posX, const double &posY, const double &posZ, const double &speed)
        : m_posX{posX}, m_posY{posY}, m_posZ{posZ}, m_speed{speed} { }
    void render() const;
    void fly(double x, double y, double z);
private:
    double m_posX, m_posY, m_posZ;
    double m_speed;
};
