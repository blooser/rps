#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>


class Player {
public:
    Player(const std::string &name);

    struct Choice {
        char m_value;

        Choice &operator=(char);
        bool invalid() const;

        bool operator>(const Choice &other);
        bool operator<(const Choice &other);
        bool operator==(const Choice &other);

        friend std::ostream &operator<<(std::ostream &os, const Choice &choice);

        static const std::string CHARS;
        static std::unordered_map<char, std::string> NAMES;
    };

    virtual void choice();

    friend std::ostream& operator<<(std::ostream &os, const Player& player);

    friend class Game;

protected:
    std::string m_name;
    unsigned int m_score;
    Choice m_choice;
};

class Bot : public Player {
public:
    Bot();

    void choice() override;

    friend class Game;

private:
    static int counter;
};

#endif // PLAYER_H
