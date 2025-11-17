#ifndef WORDLE_H
#define WORDLE_H

#include "Game.h"
#include "Leaderboard.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Wordle : public Game {
private:
    std::string secretWord;
    std::vector<std::string> guesses;
    const int WORD_LENGTH = 5;
    const int MAX_ATTEMPTS = 6;
    bool gameOver;
    
    std::string toUpper(std::string s) const;
    void generateSecret();

public:
    Wordle(std::string playerName = "Player");

    void showLogo() const override;
    void showRules() override;
    void start() override;
    void reset() override;
    void display() const override;
};

#endif
