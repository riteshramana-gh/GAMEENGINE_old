#include "Game.h"

Game::Game(string gName, string pName, int s)
    : gameName(gName), player(pName, gName, s) {}  

Game::~Game() {}
ostream& operator<<(ostream& out, const Game& g) {
    g.display();  
    return out;
}
