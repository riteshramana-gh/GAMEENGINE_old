#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "player.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

class Leaderboard {
private:
    string filename;
    vector<Player> players;

    
    void sortByScore() {
        sort(players.begin(), players.end(),
             [](const Player& a, const Player& b) {
                 return a.score > b.score;
             });
    }

public:
    
    Leaderboard(string gameName = "General") {
        filename = gameName + "_lb.txt";
        load();
    }

    
    void load() {
        players.clear();
        ifstream fin(filename);
        if (!fin) return;

        string name, game;
        int score;

        
        while (fin >> name >> game >> score)
            players.push_back(Player(name, game, score));

        fin.close();
        sortByScore();
    }

    
    void save() const {
        ofstream fout(filename);
        for (auto& p : players)
            fout << p.name << " " << p.currentGame << " " << p.score << "\n";
        fout.close();
    }

    
    Leaderboard& operator+(const Player& p) {
        bool found = false;
        for (auto& existing : players) {
            if (existing.name == p.name && existing.currentGame == p.currentGame) {
                existing.score = max(existing.score, p.score);
                found = true;
                break;
            }
        }
        if (!found)
            players.push_back(p);

        sortByScore();
        save();
        return *this;
    }

    
    
    Leaderboard operator+(const Leaderboard& other) const {
        Leaderboard combined("MainLeaderboard");
        combined.players = players;

        for (const auto& p : other.players) {
            bool found = false;
            for (auto& existing : combined.players) {
                if (existing.name == p.name) { 
                    existing.score += p.score; 
                    found = true;
                    break;
                }
            }
            if (!found)
                combined.players.push_back(p);
        }

        combined.sortByScore();
        return combined;
    }

    
    friend ostream& operator<<(ostream& out, const Leaderboard& lb) {
        out << "\n🏆 Leaderboard: " << lb.filename <<"\n";
        out << "---------------------------------\n";
        int rank = 1;
        for (const auto& p : lb.players)
            out << rank++ << ". " << p.name << " - " << p.score << "\n";
        out << "---------------------------------\n";
        return out;
    }
};

#endif
