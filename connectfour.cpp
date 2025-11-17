#include "connectfour.h"
#include "Leaderboard.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm>
using namespace std;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"


#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

#define RED_TOKEN   "🔴"
#define YELLOW_TOKEN "🟡"
#define EMPTY_SLOT  "🔳"

Connect4::Connect4(string playerName)
    : Game("Connect4", playerName, 0), currentPlayer('X') {
    reset();
}

void Connect4::showRules() {
    cout << YELLOW << "\nConnect 4 Rules:\n" << RESET;
    cout << "1. You (Player 1) are " << RED_TOKEN << " and AI is " << YELLOW_TOKEN << ".\n";
    cout << "2. Drop tokens into columns (0–6) to connect four in a row.\n";
    cout << "3. The first to connect 4 (horizontally, vertically, diagonally) wins.\n";
    cout << "4. " << EMPTY_SLOT << " = Empty slot.\n\n";
}

void Connect4::reset() {
    board.assign(ROWS, vector<char>(COLS, '.'));
    currentPlayer = 'X';
}

void Connect4::drawBoard() const {
    system(CLEAR_CMD);
    cout << CYAN << "\n ======= CONNECT 4 =======\n" << RESET;
    cout << "    ";
    for (int c = 0; c < COLS; ++c) cout << c << "  ";
    cout << "\n";
    for (int r = 0; r < ROWS; ++r) {
        cout << " | ";
        for (int c = 0; c < COLS; ++c) {
            char cell = board[r][c];
            if (cell == '.') cout << EMPTY_SLOT << " ";
            else if (cell == 'X') cout << RED_TOKEN << " ";
            else cout << YELLOW_TOKEN << " ";
        }
        cout << "|\n";
    }
    cout << "   ";
    for (int c = 0; c < COLS; ++c) cout << "⬇️  ";
    cout << "\n";
}

bool Connect4::makeMove(int col) {
    if (col < 0 || col >= COLS) return false;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == '.') {
            board[r][col] = currentPlayer;
            return true;
        }
    }
    return false;
}

void Connect4::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool Connect4::checkWin(char s) const {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == s && board[r][c+1] == s && board[r][c+2] == s && board[r][c+3] == s)
                return true;

    for (int c = 0; c < COLS; ++c)
        for (int r = 0; r < ROWS - 3; ++r)
            if (board[r][c] == s && board[r+1][c] == s && board[r+2][c] == s && board[r+3][c] == s)
                return true;

    for (int r = 0; r < ROWS - 3; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == s && board[r+1][c+1] == s && board[r+2][c+2] == s && board[r+3][c+3] == s)
                return true;

    for (int r = 3; r < ROWS; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == s && board[r-1][c+1] == s && board[r-2][c+2] == s && board[r-3][c+3] == s)
                return true;

    return false;
}

bool Connect4::checkDraw() const {
    for (int c = 0; c < COLS; ++c)
        if (board[0][c] == '.') return false;
    return true;
}


int Connect4::evaluateBoard() const {
    if (checkWin('O')) return +100000;
    if (checkWin('X')) return -100000;
    return 0;
}


int Connect4::minimax(int depth, bool isMaximizing, int alpha, int beta) {
    int eval = evaluateBoard();
    if (depth == 0 || eval != 0 || checkDraw()) return eval;

    if (isMaximizing) {
        int maxEval = -1e9;
        for (int c = 0; c < COLS; ++c) {
            for (int r = ROWS - 1; r >= 0; --r) {
                if (board[r][c] == '.') {
                    board[r][c] = 'O';
                    int score = minimax(depth - 1, false, alpha, beta);
                    board[r][c] = '.';
                    maxEval = max(maxEval, score);
                    alpha = max(alpha, score);
                    if (beta <= alpha) return maxEval;
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1e9;
        for (int c = 0; c < COLS; ++c) {
            for (int r = ROWS - 1; r >= 0; --r) {
                if (board[r][c] == '.') {
                    board[r][c] = 'X';
                    int score = minimax(depth - 1, true, alpha, beta);
                    board[r][c] = '.';
                    minEval = min(minEval, score);
                    beta = min(beta, score);
                    if (beta <= alpha) return minEval;
                    break;
                }
            }
        }
        return minEval;
    }
}


int Connect4::getBestMove() {
    int bestScore = -1e9;
    int bestCol = 3; 
    for (int c = 0; c < COLS; ++c) {
        for (int r = ROWS - 1; r >= 0; --r) {
            if (board[r][c] == '.') {
                board[r][c] = 'O';
                int score = minimax(6, false, -1e9, 1e9);
                board[r][c] = '.';
                if (score > bestScore) {
                    bestScore = score;
                    bestCol = c;
                }
                break;
            }
        }
    }
    return bestCol;
}

void Connect4::showLogo() const {
   string logo[] = {
             "   _______  _______  _        _        _______  _______ _________ ___   ",
             "  (  ____ \\(  ___  )( (    /|( (    /|(  ____ \\(  ____  \\__   __//   )  ",
             "  | (    \\/| (   ) ||  \\  ( ||  \\  ( || (    \\/| (    \\/   ) (  / /) |  ",
             "  | |      | |   | ||   \\ | ||   \\ | || (__    | |         | | / (_) (_ ",
             "  | |      | |   | || (\\ \\) || (\\ \\) ||  __)   | |         | |(____   _)",
             "  | |      | |   | || | \\   || | \\   || (      | |         | |     ) (  ",
             "  | (____/\\| (___) || )  \\  || )  \\  || (____/\\| (____/\\   | |     | |  ",
             "  (_______/(_______)|/    )_)|/    )_)(_______/(_______/   )_(     (_)  "
            };
    system(CLEAR_CMD);

    for (int i = 0; i < 8; i++) {
        cout <<GREEN << logo[i] << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Connect4::start() {
    showRules();
    cout << "Press Enter to continue...";

    while (true) {
        cout << *this;

        if (currentPlayer == 'X') {
            int col;
            cout << YELLOW << "\nYour turn (" << RED_TOKEN << "), choose a column (0–6): " << RESET;
            cin >> col;

            if (!cin || !makeMove(col)) {
                cout << RED << " Invalid move. Try again." << RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                this_thread::sleep_for(chrono::milliseconds(700));
                continue;
            }
        } else {
            cout << CYAN << "\nAI is thinking..." << RESET << endl;
            int aiCol = getBestMove();
            makeMove(aiCol);
            this_thread::sleep_for(chrono::milliseconds(700));
        }

        if (checkWin(currentPlayer)) {
            cout << *this;

            if (currentPlayer == 'X') {
                cout << GREEN << "\n You win! \n" << RESET;
                player += 50;  
            } else {
                cout << RED << "\n AI wins! \n" << RESET;
            }

            
            Leaderboard lb(gameName);
            lb = lb + player;

            cout << CYAN << "\n Current " << gameName << " Leaderboard:\n" << RESET;
            cout << lb;  
            this_thread::sleep_for(chrono::milliseconds(1000));
            break;
        }

        if (checkDraw()) {
            cout << *this;
            cout << CYAN << "\nIt's a draw! \n" << RESET;
            break;
        }

        switchPlayer();
    }
}

void Connect4::display() const {
    drawBoard();
}
 