#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Game.h"
#include "Leaderboard.h"
#include <iostream>
#include <vector>
#include <limits>

class Tictactoe : public Game {
private:
    char board[3][3];
    char playerMark, aiMark;
    bool gameOver;

    void drawBoard() const;
    bool isMovesLeft() const;
    int evaluate() const;
    int minimax(bool isMax);
    std::pair<int, int> findBestMove();
    void makeMove(int r, int c, char mark);
    bool checkWin(char mark) const;
    bool checkDraw() const;

public:
    Tictactoe(std::string playerName = "Player");

    void showRules() override;
    void start() override;
    void reset() override;
    void display() const override;
};

#endif
