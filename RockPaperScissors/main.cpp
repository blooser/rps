#include <iostream>
#include <Game.h>


int main(void) {
    std::string name;
    int bots;

    std::cout << "Nickname: ";
    std::cin >> name;

    std::cout << "Bots: ";
    std::cin >> bots;

    Game game(name, bots);
    game.exec();
}
