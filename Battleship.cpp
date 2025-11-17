
#include "Battleship.h"
#include "leaderboard.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>
#include <limits>
using namespace std;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"


#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif


Battleship::Battleship(string playerName)
    : Game("Battleship", playerName, 0), size(5) {  
    reset();
}


void Battleship::showRules() {
    cout << YELLOW << "\nBattleship Rules:\n";
    cout << "1. Place ships manually on a 5x5 grid (rows A-E, cols 0-4).\n";
    cout << "2. Each ship has a size (2, 3, 3, 4) and can be horizontal or vertical.\n";
    cout << "3. Try to hit and sink all enemy ships before yours are sunk.\n";
    cout << "4. 💥 = Hit, ⚪ = Miss, 🚢 = Your ship, 🌊 = Water.\n" << RESET;
}


void Battleship::reset() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            playerGrid[i][j] = "~";  
            aiGrid[i][j] = "~";
            aiView[i][j] = "~";
            playerShips[i][j] = false;
            aiShips[i][j] = false;
        }
    aiHits.clear();
    placeAIShips();
}


bool Battleship::canPlaceShip(bool gridShips[][5], int r, int c, int len, bool horizontal) const {
    if (horizontal) {
        if (c + len > size) return false;
        for (int i = 0; i < len; ++i)
            if (gridShips[r][c + i]) return false;
    } else {
        if (r + len > size) return false;
        for (int i = 0; i < len; ++i)
            if (gridShips[r + i][c]) return false;
    }
    return true;
}


void Battleship::placeShipOn(bool gridShips[][5], std::string grid[][5], int r, int c, int len, bool horizontal) {
    for (int i = 0; i < len; ++i) {
        int rr = r + (horizontal ? 0 : i);
        int cc = c + (horizontal ? i : 0);
        gridShips[rr][cc] = true;
        if (grid != nullptr)
            grid[rr][cc] = "🚢";
    }
}


void Battleship::placeAIShips() {
    std::mt19937 gen((unsigned)time(nullptr));
    for (int len : shipSizes) {
        bool placed = false;
        std::uniform_int_distribution<> distDir(0, 1);
        while (!placed) {
            int r = rand() % size;
            int c = rand() % size;
            bool horizontal = (distDir(gen) == 1);
            if (canPlaceShip(aiShips, r, c, len, horizontal)) {
                placeShipOn(aiShips, aiGrid, r, c, len, horizontal);
                placed = true;
            }
        }
    }
    for (int i=0;i<size;++i)
        for (int j=0;j<size;++j)
            aiGrid[i][j] = "~";  
}


void Battleship::placePlayerShips() {
    cout << YELLOW << "\nPlace your ships on the 5x5 grid.\n" << RESET;
    cout << "Ship sizes: ";
    for (size_t i=0;i<shipSizes.size();++i)
        cout << shipSizes[i] << (i+1<shipSizes.size()? ", " : "\n");
    this_thread::sleep_for(chrono::milliseconds(1000));
    for (int len : shipSizes) {
        bool placed = false;
        while (!placed) {
            drawBoardsSideBySide();
            cout << YELLOW << "\nPlacing ship of length " << len << RESET << endl;
            cout << "Row (A-E): ";
            char rowc; cin >> rowc; rowc = toupper(rowc);
            cout << "Column (0-4): ";
            int col; cin >> col;
            cout << "Orientation (H/V): ";
            char o; cin >> o; o = toupper(o);

            if (rowc < 'A' || rowc > 'A' + size - 1 || col < 0 || col >= size || (o != 'H' && o != 'V')) {
                cout << RED << "Invalid input. Try again.\n" << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                this_thread::sleep_for(chrono::milliseconds(700));
                continue;
            }

            int r = rowc - 'A';
            bool horizontal = (o == 'H');

            if (!canPlaceShip(playerShips, r, col, len, horizontal)) {
                cout << RED << "Cannot place there. Try again.\n" << RESET;
                this_thread::sleep_for(chrono::milliseconds(700));
                continue;
            }

            placeShipOn(playerShips, playerGrid, r, col, len, horizontal);
            placed = true;
        }
    }
}


void Battleship::drawBoardsSideBySide() const {
    system(CLEAR_CMD);

    cout << CYAN << "Your Board" << RESET;
    int spacing = 10;
    for (int i=0;i<spacing;i++) cout << ' ';
    cout << CYAN << "       AI Board" << RESET << "\n\n";

    cout << "   ";
    for (int c = 0; c < size; ++c) cout << " " << c << " ";
    for (int i=0;i<spacing-3;i++) cout << ' ';
    cout << "      ";
    for (int c = 0; c < size; ++c) cout << " " << c << " ";
    cout << "\n";

    for (int r = 0; r < size; ++r) {
        cout << " " << char('A' + r) << " ";
        for (int c = 0; c < size; ++c) {
            string cell = playerGrid[r][c];
            if (cell == "~") cout << CYAN << "🌊 " << RESET;
            else if (cell == "🚢") cout << GREEN << "🚢 " << RESET;
            else if (cell == "💥") cout << RED << "💥 " << RESET;
            else if (cell == "⚪") cout << CYAN << "⚪ " << RESET;
        }

        for (int i=0;i<spacing;i++) cout << ' ';
        cout << " " << char('A' + r) << " ";

        for (int c = 0; c < size; ++c) {
            string cell = aiView[r][c];
            if (cell == "~") cout << CYAN << "🌊 " << RESET;
            else if (cell == "💥") cout << RED << "💥 " << RESET;
            else if (cell == "⚪") cout << CYAN << "⚪ " << RESET;
        }
        cout << "\n";
    }
}


bool Battleship::allAIShipsSunk() const {
    for (int r=0;r<size;++r)
        for (int c=0;c<size;++c)
            if (aiShips[r][c] && aiView[r][c] != "💥") return false;
    return true;
}
bool Battleship::allPlayerShipsSunk() const {
    for (int r=0;r<size;++r)
        for (int c=0;c<size;++c)
            if (playerShips[r][c] && playerGrid[r][c] != "💥") return false;
    return true;
}


void Battleship::aiTurn() {
    static Coord lastHit{-1, -1};
    static Coord direction{0, 0};  
    static bool axisLocked = false;

    Coord target{-1, -1};

    
    if (axisLocked && lastHit.r != -1) {
        int nr = lastHit.r + direction.r;
        int nc = lastHit.c + direction.c;
        if (nr >= 0 && nr < size && nc >= 0 && nc < size &&
            (playerGrid[nr][nc] == "~" || playerGrid[nr][nc] == "🚢")) {
            target = {nr, nc};
        } else {
            
            direction.r = -direction.r;
            direction.c = -direction.c;
            lastHit = aiHits.front();  
            int orr = lastHit.r + direction.r;
            int occ = lastHit.c + direction.c;
            if (orr >= 0 && orr < size && occ >= 0 && occ < size &&
                (playerGrid[orr][occ] == "~" || playerGrid[orr][occ] == "🚢")) {
                target = {orr, occ};
            } else {
                
                axisLocked = false;
                direction = {0, 0};
            }
        }
    }

    
    if (!axisLocked && lastHit.r != -1 && target.r == -1) {
        vector<Coord> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
        std::shuffle(dirs.begin(), dirs.end(), std::mt19937((unsigned)time(nullptr)));
        for (auto d : dirs) {
            int nr = lastHit.r + d.r;
            int nc = lastHit.c + d.c;
            if (nr >= 0 && nr < size && nc >= 0 && nc < size &&
                (playerGrid[nr][nc] == "~" || playerGrid[nr][nc] == "🚢")) {
                target = {nr, nc};
                direction = d;
                break;
            }
        }
    }

    
    if (target.r == -1) {
        vector<Coord> cells;
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                if (playerGrid[r][c] == "~" || playerGrid[r][c] == "🚢")
                    cells.push_back({r, c});
        std::shuffle(cells.begin(), cells.end(), std::mt19937((unsigned)time(nullptr)));
        target = cells.front();
    }

    
    bool hit = playerShips[target.r][target.c];
    if (hit) {
        playerGrid[target.r][target.c] = "💥";
        cout << "\nAI attacks " << char('A'+target.r) << target.c
             << " -> " << RED << "💥 Hit!" << RESET << endl;
        aiHits.push_back(target);

        
        if (lastHit.r != -1 && !axisLocked) {
            if (lastHit.r == target.r) { direction = {0, (target.c > lastHit.c) ? 1 : -1}; axisLocked = true; }
            else if (lastHit.c == target.c) { direction = {(target.r > lastHit.r) ? 1 : -1, 0}; axisLocked = true; }
        }

        lastHit = target;
    } else {
        playerGrid[target.r][target.c] = "⚪";
        cout << "\nAI attacks " << char('A'+target.r) << target.c
             << " -> " << CYAN << "⚪ Miss!" << RESET << endl;

        
        if (axisLocked) {
            direction.r = -direction.r;
            direction.c = -direction.c;
            lastHit = aiHits.front(); 
        } else if (lastHit.r != -1) {
            
            lastHit = {-1, -1};
        }
    }

    this_thread::sleep_for(chrono::milliseconds(900));
}

void Battleship::showLogo() const {
    string logo[] = {
                "██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗",
                "██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗",
                "██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██║  ██║",
                "██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██████║",
                "██║  ██║██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██╔╝",
                "██████╗╝╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝██╝ ",
                "╚═════╝                                                              ╚═╝ "
            };
    system(CLEAR_CMD);
    for (int i = 0; i < 7; i++) {
        cout <<GREEN << logo[i] << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Battleship::start() {
    showRules();
    cout<<endl;
    cout << "Press Enter to continue...";
    cin.get();

    placePlayerShips();

    for (int r=0;r<size;++r)
        for (int c=0;c<size;++c) aiView[r][c] = "~";

    while (true) {
        cout << *this; 

        cout << YELLOW << "\nYour move. Row (A-E): " << RESET;
        char rowc; cin >> rowc; rowc = toupper(rowc);
        cout << "Column (0-4): ";
        int col; cin >> col;

        if (rowc < 'A' || rowc > 'A' + size - 1 || col < 0 || col >= size) {
            cout << RED << "Invalid input.\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(700));
            continue;
        }

        int r = rowc - 'A';

        if (aiView[r][col] == "💥" || aiView[r][col] == "⚪") {
            cout << YELLOW << "Already attacked. Pick another.\n" << RESET;
            continue;
        }

        if (aiShips[r][col]) {
            aiView[r][col] = "💥";
            cout << GREEN << "\n💥 Hit!" << RESET << endl;
            player += 10; 
        } else {
            aiView[r][col] = "⚪";
            cout << CYAN << "\n⚪ Miss!" << RESET << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(700));

        if (allAIShipsSunk()) {
            cout << *this;
            cout << GREEN << "\n🎉 You sank all AI ships! You win!\n" << RESET;

            
            player += 50;

            
            Leaderboard lb(gameName);
            lb = lb + player;

            cout << CYAN << "\n Current " << gameName << " Leaderboard:\n" << RESET;
            cout << lb;  

            break;
        }

        aiTurn();

        if (allPlayerShipsSunk()) {
            cout << *this;
            cout << RED << "\n All your ships were sunk. You lost.\n" << RESET;

            
            
            Leaderboard lb(gameName);
            lb = lb + player;

            cout << CYAN << "\n Current " << gameName << " Leaderboard:\n" << RESET;
            cout << lb;
            this_thread::sleep_for(chrono::milliseconds(1000));
            break;
        }

    }

    
    
}


void Battleship::display() const {
    drawBoardsSideBySide();
}
