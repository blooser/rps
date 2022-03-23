#include "Game.h"
#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include <cassert>


Game::Game(const std::string &name, const int bots)
    : m_player(name),
      m_bots(bots) {

}

void Game::exec() {
    LOOP {
        Bot& bot = m_bots.next();

        BEGIN_ROUND

        std::cout << m_player << " vs " << bot << "\n";

        auto playerChoice = m_player.choice();

        DelayedBotChoice delayedBotChoice = DelayedBotChoice{bot};
        auto future = delayedBotChoice.promise.get_future();

        std::thread t(std::ref(delayedBotChoice));
        t.detach(); // NOTE: Bye!

        auto botChoice = future.get();

        resolve(playerChoice, botChoice);

        END_ROUND
    }
}

void Game::resolve(Player::Choice& playerChoice, Bot::Choice& botChoice) {
    auto& score = m_scoring.get(playerChoice.player, botChoice.player);

    if (playerChoice > botChoice) {
        score.playerScore += 2;

        std::cout << playerChoice.player << " won! (" << playerChoice << " > " << botChoice << ")\n";
    }

    if (playerChoice < botChoice) {
        score.botScore += 2;

        std::cout << botChoice.player << " won! (" << botChoice << " > " << playerChoice << ")\n";
    }

    if (playerChoice == botChoice) {
         score.playerScore += 1;
         score.botScore += 1;

         std::cout << "Tie for " << playerChoice.player << " and " << botChoice.player << "\n";
    }

    std::cout << score;
}


Scoring::Scoring() {}

Scoring::Score::Score(Player &p, Player &b)
    : player(p),
      playerScore(0),
      bot(b),
      botScore(0) {

}

std::ostream &operator<<(std::ostream &os, const Scoring::Score &score) {
    return os << score.player << " score: " << score.playerScore
              << " | "
              << score.bot << " score: " << score.botScore << "\n";
}

bool Scoring::Score::operator==(const Score &score) {
    return score.player == score.player and
           score.bot == bot;
}

Scoring::Score& Scoring::get(Player &player, Player &bot) {
    Score sc = Score(player, bot);

    auto it = std::find_if(m_scores.begin(), m_scores.end(), [&](Score &s){
        return s == sc;
    });

    if (it == m_scores.end()) {
        m_scores.push_back(sc);

        return m_scores.back();
    }

    return *it;
}



