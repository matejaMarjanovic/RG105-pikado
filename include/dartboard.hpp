#pragma once

#include "lighting.hpp"
#include <cmath>


class DartboardCircle {
public:
    DartboardCircle(const double &radius)
        : m_radius{radius} { }
    void render(void) const;
private:
    void drawBigCircle() const;
    void drawLineCircle1() const;
    void drawLineCircle2() const;
    void drawCentralCirlces() const;
    double m_radius;
};


class Dartboard {
public:
    Dartboard(const DartboardCircle &dartCirc, const double &width, const double &height)
        :m_dartCirc{dartCirc}, 
         m_width{width}, 
         m_height{height} { }
    void render() const;
private:
    DartboardCircle m_dartCirc;
    double m_width, m_height;
};
