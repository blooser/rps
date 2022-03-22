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

        auto playerChoice = m_player.choice();
        auto botChoice = bot.choice();

        resolve(playerChoice, botChoice);

        std::cout << "Player score: " << m_player.m_score << "\n";
    }
}

void Game::resolve(Player::Choice& playerChoice, Bot::Choice& botChoice) {
    if (playerChoice > botChoice) {
        win(playerChoice.player);
        return;
    }

    if (playerChoice < botChoice) {
        win(botChoice.player);
        return;
    }

    if (playerChoice == botChoice) {
        win(playerChoice.player, botChoice.player);
    }
}

template <typename Winner>
void Game::win(Winner& winner) {
    std::cout << winner << " won \n";

    winner.m_score += 2;
}

template <typename Winner, typename AnotherWinner>
void Game::win(Winner& winner1, AnotherWinner& winner2) {
    std::cout << "Tie for " << winner1 << " and " << winner2 << "\n";

    winner1.m_score += 1;
    winner2.m_score += 1;
}
