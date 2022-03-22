#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

Game::Game(const std::string &name, const int bots)
    : m_player(name),
      m_bots(bots) {

}

void Game::exec() {
    LOOP {
        Bot& bot = m_bots.next();

        std::cout << m_player << " vs " << bot << "\n";

        m_player.choice();
        bot.choice();

        resolve(m_player, bot);
    }
}

void Game::resolve(Player player, Bot bot) {
    if (player.m_choice > bot.m_choice) {
        win(player);
        return;
    }

    if (player.m_choice < bot.m_choice) {
        win(bot);
        return;
    }

    if (player.m_choice == bot.m_choice) {
        win(player, bot);
    }
}

template <typename Winner>
void Game::win(Winner winner) {
    std::cout << winner << " won with " << winner.m_choice << " choice\n";

    winner.m_score += 2;
}

template <typename Winner, typename AnotherWinner>
void Game::win(Winner winner1, AnotherWinner winner2) {
    std::cout << "Tie for " << winner1 << " and " << winner2 << "\n";

    winner1.m_score += 1;
    winner2.m_score += 1;
}
