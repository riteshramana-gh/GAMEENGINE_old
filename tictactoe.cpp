#include "Tictactoe.h"
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"


Tictactoe::Tictactoe(string playerName)
    : Game("TicTacToe", playerName, 0), playerMark('X'), aiMark('O'), gameOver(false) {
    reset();
}


void Tictactoe::reset() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    gameOver = false;
}


void Tictactoe::drawBoard() const {
    system(CLEAR_CMD);
    cout << CYAN << "\n===== TIC TAC TOE =====" << RESET << endl;
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << (board[i][j] == ' ' ? '.' : board[i][j]);
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "___|___|___\n";
    }
    cout << "\n";
}


void Tictactoe::display() const {
    drawBoard();
}


bool Tictactoe::isMovesLeft() const {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ') return true;
    return false;
}


int Tictactoe::evaluate() const {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == aiMark) return +10;
            if (board[i][0] == playerMark) return -10;
        }
    }
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == aiMark) return +10;
            if (board[0][j] == playerMark) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == aiMark) return +10;
        if (board[0][0] == playerMark) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == aiMark) return +10;
        if (board[0][2] == playerMark) return -10;
    }
    return 0;
}


int Tictactoe::minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = aiMark;
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = playerMark;
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
        return best;
    }
}


pair<int, int> Tictactoe::findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = aiMark;
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}


bool Tictactoe::checkWin(char mark) const {
    for (int i = 0; i < 3; ++i)
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return true;
    for (int j = 0; j < 3; ++j)
        if (board[0][j] == mark && board[1][j] == mark && board[2][j] == mark) return true;
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return true;
    return false;
}


bool Tictactoe::checkDraw() const {
    return !isMovesLeft();
}


void Tictactoe::makeMove(int r, int c, char mark) {
    board[r][c] = mark;
}


void Tictactoe::showRules() {
    system(CLEAR_CMD);
    cout << YELLOW << "\nTIC TAC TOE RULES:\n" << RESET;
    cout << "1. The game is played on a 3x3 grid.\n";
    cout << "2. You are X, the computer is O.\n";
    cout << "3. Take turns placing marks in empty cells.\n";
    cout << "4. The first to align 3 marks horizontally, vertically, or diagonally wins.\n";
    cout << "5. If the grid fills with no winner, it's a draw.\n";
    cout << "\nPress ENTER to continue...";
    cin.get();
}

void Tictactoe::showLogo() const {
    string logo[] = {
                " _______ _______ ______       _______ _______ ______       _______ _______ _______ ",
                "|_     _|_     _|      |_____|_     _|   _   |      |_____|_     _|       |    ___|",
                "  |   |  _|   |_|   ---|______||   | |       |   ---|______||   | |   -   |    ___|",
                "  |___| |_______|______|       |___| |___|___|______|       |___| |_______|_______|",

                };
    system(CLEAR_CMD);

    for (int i = 0; i < 4; i++) {
        cout <<GREEN << logo[i] << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Tictactoe::start() {
    showRules();

    while (!gameOver) {
        drawBoard();
        cout << CYAN << "Your move (row col): " << RESET;
        int r, c; cin >> r >> c;

        if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != ' ') {
            cout << RED << "Invalid move! Try again.\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(800));
            continue;
        }

        makeMove(r, c, playerMark);
        if (checkWin(playerMark)) {
            drawBoard();
            cout << GREEN << "\n You win!\n" << RESET;
            player += 50;
            Leaderboard lb("TicTacToe");
            lb = lb + player;
            cout << lb;
            return;
        }
        if (checkDraw()) {
            drawBoard();
            cout << YELLOW << "\nIt's a draw!\n" << RESET;
            Leaderboard lb("TicTacToe");
            lb = lb + player;
            cout << lb;
            return;
        }

        cout << "\nComputer thinking...\n";
        this_thread::sleep_for(chrono::milliseconds(600));
        pair<int, int> aiMove = findBestMove();
        makeMove(aiMove.first, aiMove.second, aiMark);

        if (checkWin(aiMark)) {
            drawBoard();
            cout << RED << "\n Computer wins!\n" << RESET;
            Leaderboard lb("TicTacToe");
            lb = lb + player;
            cout << lb;
            return;
        }
        if (checkDraw()) {
            drawBoard();
            cout << YELLOW << "\nIt's a draw!\n" << RESET;
            Leaderboard lb("TicTacToe");
            lb = lb + player;
            cout << lb;
            return;
        }
    }
}
