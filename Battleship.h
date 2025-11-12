#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Game.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

class Battleship : public Game {
private:
    
    std::string playerGrid[5][5]; 
    std::string aiGrid[5][5];     
    std::string aiView[5][5];     
    bool playerShips[5][5];
    bool aiShips[5][5];
    int size;

    struct Coord { int r, c; };

    std::vector<int> shipSizes = {2, 3, 3, 4};
    std::vector<Coord> aiHits;

    
    bool canPlaceShip(bool gridShips[][5], int r, int c, int len, bool horizontal) const;
    void placeShipOn(bool gridShips[][5], std::string grid[][5], int r, int c, int len, bool horizontal);
    void placeAIShips();
    void placePlayerShips();
    void drawBoardsSideBySide() const;
    bool allAIShipsSunk() const;
    bool allPlayerShipsSunk() const;
    void aiTurn();

public:
    
    Battleship(std::string playerName = "Player");

    
    void showRules() override;
    void start() override;
    void reset() override;

    
    void display() const override;  
};

#endif 
