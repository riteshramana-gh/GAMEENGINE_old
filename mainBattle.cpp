#include "Battleship.h"
#include "connectfour.h"
#include "Leaderboard.h"
#include "minesweeper.h"
#include "tictactoe.h" 
#include "wordle.h"
#include "templates.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <string>
#include <exception>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define ORANGE "\033[38;2;255;165;0m"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

void clearScreen() {
    system(CLEAR_COMMAND);
}

void animatedIntro() {
    clearScreen();

    string lines[] = {
        "",
       "           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::",
       "           ::########::'####:'##::::'##:'########:'##:::::::'########::'#######::'########:::'######:::'########:",
       "           ::##.... ##:. ##::. ##::'##:: ##.....:: ##::::::: ##.....::'##.... ##: ##.... ##:'##... ##:: ##.....::",
       "           ::##:::: ##:: ##:::. ##'##::: ##::::::: ##::::::: ##::::::: ##:::: ##: ##:::: ##: ##:::..::: ##:::::::",
       "           ::########::: ##::::. ###:::: ######::: ##::::::: ######::: ##:::: ##: ########:: ##::'####: ######:::",
       "           ::##.....:::: ##:::: ## ##::: ##...:::: ##::::::: ##...:::: ##:::: ##: ##.. ##::: ##::: ##:: ##...::::",
       "           ::##::::::::: ##::: ##:. ##:: ##::::::: ##::::::: ##::::::: ##:::: ##: ##::. ##:: ##::: ##:: ##:::::::",
       "           ::##::::::::'####: ##:::. ##: ########: ########: ##:::::::. #######:: ##:::. ##:. ######::: ########:",
       "           ::..:::::::::....::..:::::..::........::........::..:::::::::.......:::..:::::..:::......::::........:"
    };
    for (int i = 0; i < 10; i++) {
        cout << RED << lines[i] << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    cout << YELLOW << "\n                                                    ⚔️  MULTI-GAME ENGINE  ⚔️\n" << RESET;
    cout << "\n                                                  Press Enter to continue...";
    cin.get();
}

void gameIntro(const string logo[], int size) {
    clearScreen();

    for (int i = 0; i < size; i++) {
        cout <<GREEN << logo[i] << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// ...existing code...

// safe input parser: reads a line and converts to int, throws on invalid input
int readMenuChoice() {
    string line;
    if (!getline(cin, line)) {
        throw runtime_error("Failed to read input");
    }
    // if empty because previous >> left newline, read again
    if (line.size() == 0) {
        if (!getline(cin, line)) throw runtime_error("Failed to read input");
    }
    try {
        size_t idx = 0;
        int val = stoi(line, &idx);
        if (idx != line.size()) throw invalid_argument("Extra characters in input");
        return val;
    } catch (const invalid_argument&) {
        throw invalid_argument("Invalid input. Please enter a number (1-7).");
    } catch (const out_of_range&) {
        throw invalid_argument("Number out of range. Please enter a valid choice.");
    }
}

void mainMenu() {
    int choice;
    animatedIntro();

    while (true) {
        clearScreen();
        string lines[] = {
            "     ██████   ██████            ███                ██████   ██████                               ",
            "    ░░██████ ██████            ░░░                ░░██████ ██████                                ",
            "     ░███░█████░███   ██████   ████  ████████      ░███░█████░███   ██████  ████████   █████ ████",
            "     ░███░░███ ░███  ░░░░░███ ░░███ ░░███░░███     ░███░░███ ░███  ███░░███░░███░░███ ░░███ ░███ ",
            "     ░███ ░░░  ░███   ███████  ░███  ░███ ░███     ░███ ░░░  ░███ ░███████  ░███ ░███  ░███ ░███ ",
            "     ░███      ░███  ███░░███  ░███  ░███ ░███     ░███      ░███ ░███░░░   ░███ ░███  ░███ ░███ ",
            "     █████     █████░░████████ █████ ████ █████    █████     █████░░██████  ████ █████ ░░████████",
            "    ░░░░░     ░░░░░  ░░░░░░░░ ░░░░░ ░░░░ ░░░░░    ░░░░░     ░░░░░  ░░░░░░  ░░░░ ░░░░░   ░░░░░░░░ \n"
        };
        for (int i = 0; i < 8; i++) {
            cout << ORANGE << lines[i] << RESET << endl;
            this_thread::sleep_for(chrono::milliseconds(150));
        }

        cout << RED << "     ════════════════════════════════════ " << endl;
        cout << RED << "      ║" << CYAN << "1. Play Battleship" << RED << "              ║" << endl;
        cout << RED << "      ║" << CYAN << "2. Play Connectfour" << RED << "             ║" << endl;
        cout << RED << "      ║" << CYAN << "3. Play Minesweeper" << RED << "             ║" << endl;
        cout << RED << "      ║" << CYAN << "4. Play Wordle     " << RED << "             ║" << endl;
        cout << RED << "      ║" << CYAN << "5. Play TicTacToe  " << RED << "             ║" << endl;
        cout << RED << "      ║" << YELLOW << "6. View Leaderboard" << RED << "             ║" << endl;
        cout << RED << "      ║" << GREEN << "7. Exit" << RESET << RED << "                         ║" << endl;
        cout << RED << "     ════════════════════════════════════" << endl;
        cout << "\nEnter choice: " << RESET;

        try {
            choice = readMenuChoice();
        } catch (const exception& e) {
            cout << RED << e.what() << "\n" << RESET;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }

        if (choice == 1) {
            clearScreen();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            try {
                auto game = make_game<Battleship>(playerName);
                try {
                    game->showLogo();
                    game->start();
                } catch (const exception& e) {
                    delete game;
                    throw; // handled by outer catch below
                }
                delete game;
            } catch (const exception& e) {
                cout << RED << "Game error: " << e.what() << RESET << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 2) {
            clearScreen();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            try {
                auto game = make_game<Connect4>(playerName)
                try {
                    game->showLogo();
                    game->start();
                } catch (...) {
                    delete game;
                    throw;
                }
                delete game;
            } catch (const exception& e) {
                cout << RED << "Game error: " << e.what() << RESET << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 3) {
            clearScreen();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            try {
                auto game = make_game<Minesweeper>(9, 9, 10, playerName);
                try {
                    game->showLogo();
                    game->start();
                } catch (...) {
                    delete game;
                    throw;
                }
                delete game;
            } catch (const exception& e) {
                cout << RED << "Game error: " << e.what() << RESET << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 4) {
            clearScreen();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            try {
                auto game = make_game<Wordle>(playerName);
                try {
                    game->showLogo();
                    game->start();
                } catch (...) {
                    delete game;
                    throw;
                }
                delete game;
            } catch (const exception& e) {
                cout << RED << "Game error: " << e.what() << RESET << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 5) {
            clearScreen();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            try {
                auto game = make_game<Tictactoe>(playerName);
                try {
                    game->showLogo();
                    game->start();
                } catch (...) {
                    delete game;
                    throw;
                }
                delete game;
            } catch (const exception& e) {
                cout << RED << "Game error: " << e.what() << RESET << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }

        else if (choice == 6) {
            clearScreen();
            cout << YELLOW << "COMBINED LEADERBOARD :" << RESET << endl;

            Leaderboard battleshipLB("Battleship");
            Leaderboard connect4LB("Connect4");
            Leaderboard minesweeperLB("Minesweeper");
            Leaderboard wordleLB("Wordle");
            Leaderboard tictactoeLB("TicTacToe");

            Leaderboard combinedLB = battleshipLB + connect4LB;
            combinedLB=combinedLB+minesweeperLB;
            combinedLB=combinedLB+wordleLB;
            combinedLB=combinedLB+tictactoeLB;
            cout << combinedLB;

            cout << "\nPress Enter to return to menu...";
            cin.ignore();
            cin.get();
        }

        else if (choice == 7) {
            clearScreen();
            cout << GREEN << "Thanks for playing!" << RESET << endl;
            break;
        }
        else {
            cout << RED << "Invalid choice. Try again.\n" << RESET;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

int main() {
    try {
        mainMenu();
    } catch (const exception& e) {
        cerr << RED << "Fatal error: " << e.what() << RESET << endl;
        return 1;
    } catch (...) {
        cerr << RED << "Unknown fatal error occurred." << RESET << endl;
        return 2;
    }
    return 0;
}