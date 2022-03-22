#include <string>

#include "player.h"

#define LOOP for(;;)

#define BEGIN_ROUND std::cout << "-----------------------\n";
#define END_ROUND std::cout << "-----------------------\n\n";


class Game final {
public:
    Game(const std::string &name, const int bots);

    void exec();

protected:
    void resolve(Player::Choice&, Player::Choice&);

    template <typename Winner>
    void win(Winner& winner);

    template <typename Winner, typename AnotherWinner>
    void win(Winner& winner1, AnotherWinner& winner2);

private:
    Player m_player;
    Bots m_bots;
};


