#include "game.hpp"

void Game::render() const {
    m_dartboard.render();
    m_dart.render();
}

void Game::play() {
    m_dart.move(0, 0, m_dart.posZ() + 0.1);
}
