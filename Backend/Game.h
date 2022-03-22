#include <string>

#include "player.h"

#define LOOP for(;;)

class Game final {
public:
    Game();

    void exec();

private:
    Player m_player;
    Bot bot;
};
