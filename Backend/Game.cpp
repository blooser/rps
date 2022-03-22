#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

Game::Game() : m_player("Matt") {

}

void Game::exec() {
    m_player.choice();
    bot.choice();
}
