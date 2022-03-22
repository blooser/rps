#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

#define START 0
#define ZERO 0

class Player {
public:
    Player(const std::string &name);

    struct Choice {
        Choice(Player&);

        char m_value;
        Player& player;

        Choice &operator=(char);
        bool invalid() const;

        bool operator>(const Choice &other);
        bool operator<(const Choice &other);
        bool operator==(const Choice &other);

        friend std::ostream &operator<<(std::ostream &os, const Choice &choice);

        static const std::string CHARS;
        static std::unordered_map<char, std::string> NAMES;
    };

    virtual Choice choice();

    friend std::ostream& operator<<(std::ostream &os, const Player& player);

    friend class Game;

protected:
    std::string m_name;
    unsigned int m_score;
};

class Bot : public Player {
public:
    Bot();

    Choice choice() override;

    friend class Game;

private:
    static int counter;
};

class Bots {
public:
    Bots(const int n);

    Bot& next();
    const int size() const;

private:
    const int m_bots_n;
    std::vector<Bot> m_bots;
    std::vector<Bot>::iterator m_current_bot_it;
};

#endif // PLAYER_H
