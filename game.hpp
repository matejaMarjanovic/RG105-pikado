#pragma once

#include "dartboard.hpp"
#include "dart.hpp"

class Game {
public:
    Game(Dartboard dartboard, Dart dart)
        : m_dartboard{dartboard}, m_dart{dart} { }
    void render() const;
    void play();
private:
    Dartboard m_dartboard;
    Dart m_dart;
};
