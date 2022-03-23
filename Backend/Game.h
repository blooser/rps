#include <string>

#include "player.h"

#define LOOP for(;;)

#define BEGIN_ROUND std::cout << "-----------------------\n";
#define END_ROUND std::cout << "-----------------------\n\n";


class Scoring {
public:
    Scoring();

    struct Score {
        Score(Player &p, Player &b);

        Player &player;
        unsigned int playerScore;

        Player &bot;
        unsigned int botScore;

        bool operator==(const Score&);

        friend std::ostream &operator<<(std::ostream &os, const Score& score);
    };

    Score& get(Player &, Player&);

private:
    std::vector<Score> m_scores;
};


class Game final {
public:
    Game(const std::string &name, const int bots);

    void exec();

protected:
    void resolve(Player::Choice&, Player::Choice&);

private:
    Player m_player;
    Bots m_bots;
    Scoring m_scoring;
};






