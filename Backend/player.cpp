#include "player.h"

Player::Player(const std::string &name)
    : m_name(name) {

    std::cout << m_name << " " << "entered to the game. \n";
}

std::ostream &operator<<(std::ostream &os, const Player::Choice &choice) {
     return os << choice.NAMES[choice.m_value];
};

const std::string Player::Choice::CHARS = "rps";
std::unordered_map<char, std::string> Player::Choice::NAMES = {
    {'r', "Rock"},
    {'p', "Paper"},
    {'s', "Scissors"}
};

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

void Player::choice() {
    std::cout << m_name << " choice: ";

    char playerChoice;
    std::cin >> playerChoice;

    m_choice = playerChoice;

    if (m_choice.invalid()) {
        std::cerr << "Invalid choice\n";
        exit(-1);
    }

    std::cout << m_name << " choosed: " << m_choice;
}

