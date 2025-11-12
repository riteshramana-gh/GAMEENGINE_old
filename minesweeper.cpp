#include "Minesweeper.h"
#include "Leaderboard.h"
#include <iostream>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;


#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

static void sleep_for_ms(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}


Cell::Cell() : mine(false), revealed(false), flagged(false), adjacentMines(0) {}
void Cell::setMine() { mine = true; }
bool Cell::isMine() const { return mine; }
bool Cell::isRevealed() const { return revealed; }
bool Cell::isFlagged() const { return flagged; }
void Cell::toggleFlag() { if (!revealed) flagged = !flagged; }
void Cell::reveal() { if (!flagged) revealed = true; }
void Cell::setAdjacent(int n) { adjacentMines = n; }
int Cell::getAdjacent() const { return adjacentMines; }
char Cell::displayChar() const {
    if (flagged) return 'F';
    if (!revealed) return ' ';
    if (mine) return '*';
    return adjacentMines == 0 ? '.' : '0' + adjacentMines;
}


Minesweeper::Minesweeper(int r, int c, int m, string playerName)
    : Game("Minesweeper", playerName, 0),
      rows(r), cols(c), mines(m),
      grid(r, vector<Cell>(c)),
      cursorX(0), cursorY(0),
      gameOver(false), win(false) {
    placeMines();
    calculateAdjacency();
}


void Minesweeper::placeMines() {
    srand(time(0));
    int placed = 0;
    while (placed < mines) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (!grid[x][y].isMine()) {
            grid[x][y].setMine();
            placed++;
        }
    }
}


void Minesweeper::calculateAdjacency() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!grid[i][j].isMine()) {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx, ny = j + dy;
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny].isMine())
                            count++;
                    }
                grid[i][j].setAdjacent(count);
            }
}


void Minesweeper::display() const {
    system(CLEAR_CMD);
    cout << "\n   ";
    for (int j = 0; j < cols; ++j) cout << " " << j << " ";
    cout << "\n   +";
    for (int j = 0; j < cols; ++j) cout << "---+";
    cout << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < cols; ++j) {
            bool cursor = (i == cursorX && j == cursorY);
            char disp = grid[i][j].displayChar();
            string out;
            if (disp == '*') out = string(RED) + "💣" + RESET;
            else if (disp == 'F') out = string(YELLOW) + "⚑" + RESET;
            else if (disp == '.') out = string(GREEN) + "." + RESET;
            else out = string(CYAN) + disp + RESET;

            if (cursor) cout << "[" << out << "]|";
            else cout << " " << out << " |";
        }
        cout << "\n   +";
        for (int j = 0; j < cols; ++j) cout << "---+";
        cout << "\n";
    }
}


void Minesweeper::revealAll() {
    system(CLEAR_CMD);
    cout << "\n   ";
    for (int j = 0; j < cols; ++j) cout << " " << j << " ";
    cout << "\n   +";
    for (int j = 0; j < cols; ++j) cout << "---+";
    cout << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < cols; ++j) {
            char disp = grid[i][j].isMine() ? '*' : grid[i][j].displayChar();
            string out;
            if (disp == '*') out = string(RED) + "\b💣" + RESET;
            else if (disp == 'F') out = string(YELLOW) + "⚑" + RESET;
            else if (disp == '.') out = string(GREEN) + "." + RESET;
            else out = string(CYAN) + disp + RESET;
            cout << " " << out << " |";
        }
        cout << "\n   +";
        for (int j = 0; j < cols; ++j) cout << "---+";
        cout << "\n";
    }
}

void Minesweeper::move(char dir) {
    switch (tolower(dir)) {
        case 'w': if (cursorX > 0) cursorX--; break;
        case 's': if (cursorX < rows - 1) cursorX++; break;
        case 'a': if (cursorY > 0) cursorY--; break;
        case 'd': if (cursorY < cols - 1) cursorY++; break;
    }
}


void Minesweeper::revealCell() {
    Cell& c = grid[cursorX][cursorY];
    if (c.isFlagged() || c.isRevealed()) return;
    c.reveal();
    if (c.isMine()) { gameOver = true; win = false; return; }
    if (c.getAdjacent() == 0) floodReveal(cursorX, cursorY);
    checkWin();
}


void Minesweeper::floodReveal(int x, int y) {
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                Cell& n = grid[nx][ny];
                if (!n.isRevealed() && !n.isMine()) {
                    n.reveal();
                    if (n.getAdjacent() == 0) floodReveal(nx, ny);
                }
            }
        }
}


void Minesweeper::toggleFlag() { grid[cursorX][cursorY].toggleFlag(); }


void Minesweeper::checkWin() {
    for (auto& row : grid)
        for (auto& c : row)
            if (!c.isMine() && !c.isRevealed())
                return;
    win = true;
    gameOver = true;
}


void Minesweeper::play() {
    while (!gameOver) {
        display();
        cout << YELLOW << "\nControls: W/A/S/D move | E = Reveal | F = Flag | Q = Quit\n" << RESET;
#ifdef _WIN32
        char key = _getch();
#else
        char key; cin >> key;
#endif
        if (key == 'q' || key == 'Q') break;
        else if (key == 'w' || key == 'a' || key == 's' || key == 'd') move(key);
        else if (key == 'e' || key == 'E') revealCell();
        else if (key == 'f' || key == 'F') toggleFlag();
    }

    revealAll();
    if (win) {
        cout << GREEN << "\n🎉 You cleared the field! GG!\n" << RESET;
        player += 50;
    } else {
        cout << RED << "\n💥 You hit a mine! Game over.\n" << RESET;
    }

    Leaderboard lb(gameName);
    lb = lb + player;
    cout << CYAN << "\n📊 Current " << gameName << " Leaderboard:\n" << RESET;
    cout << lb;
    sleep_for_ms(1000);
}


void Minesweeper::showRules() {
    cout << YELLOW << "\nMinesweeper Rules:\n";
    cout << "1. Uncover all cells that do not contain mines.\n";
    cout << "2. Use 'W/A/S/D' to move, 'E' to reveal, 'F' to flag.\n";
    cout << "3. Avoid revealing a mine!\n" << RESET;
}


void Minesweeper::reset() {
    grid = vector<vector<Cell>>(rows, vector<Cell>(cols));
    cursorX = cursorY = 0;
    gameOver = false;
    win = false;
    placeMines();
    calculateAdjacency();
}


void Minesweeper::start() {
    showRules();
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    play();
}
