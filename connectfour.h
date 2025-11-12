#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "Game.h"
#include <vector>
#include <string>
using namespace std;



class Connect4 : public Game {
private:
    
    static const int ROWS = 6;
    static const int COLS = 7;
    
    
    vector<vector<char>> board;

    
    char currentPlayer;

    void drawBoard() const;
    bool makeMove(int col);
    void switchPlayer();
    bool checkWin(char s) const;
    bool checkDraw() const;
    void resetBoard();

    
    int evaluateBoard() const;
    int minimax(int depth, bool isMaximizing, int alpha, int beta);
    int getBestMove();

public:
    
    Connect4(string playerName = "Player");

    
    void showRules() override;
    void start() override;
    void reset() override;
    void display() const override;
};

#endif
