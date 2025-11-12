#ifndef GAME_H
#define GAME_H
#include"Player.h"
#include <iostream>
#include <string>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"


class Game {
protected:
    string gameName;   
    Player player;
public:
    Game(string gName = "Game", string pName = "Player", int s = 0);

    ~Game();

    
    virtual void display() const = 0;

    
    friend ostream& operator<<(ostream& out, const Game& g);

    
    virtual void start() = 0;
    virtual void showRules() = 0;
    virtual void reset() = 0;
};

#endif
