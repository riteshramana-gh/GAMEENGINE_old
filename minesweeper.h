#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Game.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

class Cell {
    bool mine;
    bool revealed;
    bool flagged;
    int adjacentMines;

public:
    Cell();
    void setMine();
    bool isMine() const;
    bool isRevealed() const;
    bool isFlagged() const;
    void toggleFlag();
    void reveal();
    void setAdjacent(int n);
    int getAdjacent() const;
    char displayChar() const;
};

class Minesweeper : public Game {
    int rows, cols, mines;
    std::vector<std::vector<Cell>> grid;
    int cursorX, cursorY;
    bool gameOver;
    bool win;

    void placeMines();
    void calculateAdjacency();
    void floodReveal(int x, int y);
    void revealAll();

public:
    Minesweeper(int r = 9, int c = 9, int m = 10, std::string playerName = "Player");

    void showLogo() const override;
    void showRules() override;
    void start() override;
    void reset() override;
    void display() const override;

    void move(char dir);
    void revealCell();
    void toggleFlag();
    void checkWin();
    void play();
};

#endif
