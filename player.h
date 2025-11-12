#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    string name;
    int score;
    string currentGame;

    Player(string n = "Player", string g = "None", int s = 0)
        : name(n), currentGame(g), score(s) {}
    
    
    Player& operator+=(int points) {
        score += points;
        return *this;
    }

};

#endif