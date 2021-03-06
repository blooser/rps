#include "player.h"

#include <random>
#include <thread>
#include <chrono>
#include <chrono>

using std::chrono::milliseconds;

const std::string Player::Choice::CHARS = "rps";
std::unordered_map<char, std::string> Player::Choice::NAMES = {
    {'r', "Rock"},
    {'p', "Paper"},
    {'s', "Scissors"}
};


class RandomChar{
public:
    RandomChar(const std::string& chars)
        : m_chars(chars),
          distrib(START, chars.size()-1) {}

    char operator()() {
        return m_chars[distrib(device)];
    };

private:
    std::string m_chars;
    std::random_device device;
    std::uniform_int_distribution<> distrib;
};

RandomChar randomChar {Player::Choice::CHARS};

Player::Player(const std::string &name)
    : m_name(name),
      m_score(ZERO) {

    std::cout << m_name << " " << "entered to the game. \n";
}

std::ostream &operator<<(std::ostream &os, const Player::Choice &choice) {
     return os << choice.NAMES[choice.m_value];
};


Player::Choice::Choice(Player& _player)
    : player(_player),
      m_value('\0') {}

Player::Choice &Player::Choice::operator=(char choice) {
    m_value = choice;

    return *this;
};

bool Player::Choice::invalid() const {
    return not std::any_of(CHARS.begin(), CHARS.end(), [this](char c){
        return c == m_value;
    });
}

bool Player::Choice::operator>(const Choice &other) {
    return ((m_value == 'r' && other.m_value == 's') ||
            (m_value == 's' && other.m_value == 'p') ||
            (m_value == 'p' && other.m_value == 'r'));
}

bool Player::Choice::operator<(const Choice &other) {
    return ((m_value == 'r' && other.m_value == 'p') ||
            (m_value == 's' && other.m_value == 'r') ||
            (m_value == 'p' && other.m_value == 's'));
}

bool Player::Choice::operator==(const Choice &other) {
    return m_value == other.m_value;
}

std::ostream& operator<<(std::ostream &os, const Player &player) {
    return os << player.m_name;
};

Player::Choice Player::choice() {
    Choice choice(*this);
    char playerChoice;

    while (choice.invalid()) {
        std::cout << m_name << " choice (rps): ";

        std::cin >> playerChoice;

        choice = playerChoice;

        if (choice.invalid()) {
            std::cerr << "Invalid choice\n";
            continue;
        }

        std::cout << m_name << " choosed: " << choice << "\n";
    }

    return choice;
}

bool Player::operator==(const Player &player) {
    return m_name == player.m_name;
}

int Bot::counter = START;

Bot::Bot() : Player("Bot" + std::to_string(++counter)) {

}

Player::Choice Bot::choice() {
    Choice choice(*this);
    choice = randomChar();

    std::cout << m_name << " choosed: " << choice << "\n";

    return choice;
}

Bots::Bots(const int n) : m_bots_n(n) {
    std::cout << "Spawning " << n << " bots\n";

    m_bots.reserve(m_bots_n);
    for (int i=START; i<n; ++i) {
        m_bots.push_back(Bot());
    }

    m_current_bot_it = m_bots.begin();
}

const int Bots::size() const {
    return m_bots.size();
}

Bot& Bots::next() {
    auto current_bot_it = m_current_bot_it;

    m_current_bot_it = std::next(m_current_bot_it);

    if (m_current_bot_it == m_bots.end()) {
        m_current_bot_it = m_bots.begin();
    }

    return *current_bot_it;
}


void DelayedBotChoice::operator()() {
    std::cout << bot << " is thinking";

    for (int i=0; i<3; ++i) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(milliseconds(250));
    }

    std::cout << "\n" << std::flush;

    auto choice = bot.choice();

    promise.set_value(choice);
}

