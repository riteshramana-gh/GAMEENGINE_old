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


// ---------- Windows ----------
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
inline char getch_cross() {
    return _getch();
}

// ---------- Linux / macOS ----------
#else
#include <termios.h>
#include <unistd.h>

inline char getch_cross() {
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // no buffering, no echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore
    return ch;
}
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
    cin.sync();
cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

// ...existing code...

// safe input parser: reads a line and converts to int, throws on invalid input


int readMenuChoice() {
    cout << "\nEnter choice: " << flush;

    char ch = getch_cross();
    cout << ch << "\n";   // echo key so user sees it

    if (ch < '1' || ch > '7')
        return -1; // invalid

    return ch - '0';
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

        choice = readMenuChoice();

        if (choice == -1) {
            cout << RED << "Invalid choice!\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        // ------------ ASK NAME -----------
        string playerName;
        clearScreen();
        cout << CYAN << "\nEnter your name: " << RESET;
        getline(cin, playerName);

        // ------------ SWITCH GAMES ------------
        try {
            if (choice == 1) {
                auto game = make_game<Battleship>(playerName);
                game->showLogo();
                game->start();
            }
            else if (choice == 2) {
                auto game = make_game<Connect4>(playerName);
                game->showLogo();
                game->start();
            }
            else if (choice == 3) {
                auto game = make_game<Minesweeper>(9, 9, 10, playerName);
                game->showLogo();
                game->start();
            }
            else if (choice == 4) {
                auto game = make_game<Wordle>(playerName);
                game->showLogo();
                game->start();
            }
            else if (choice == 5) {
                auto game = make_game<Tictactoe>(playerName);
                game->showLogo();
                game->start();
            }
            else if (choice == 6) {
                clearScreen();
                cout << YELLOW << "COMBINED LEADERBOARD :" << RESET << endl;

                Leaderboard battleshipLB("Battleship");
                Leaderboard connect4LB("Connect4");
                Leaderboard minesweeperLB("Minesweeper");
                Leaderboard wordleLB("Wordle");
                Leaderboard tictactoeLB("TicTacToe");

                Leaderboard combinedLB = battleshipLB + connect4LB + minesweeperLB + wordleLB + tictactoeLB;
                cout << combinedLB;

                cout << "\nPress Enter to return...";
                cin.get();
                continue;
            }
            else if (choice == 7) {
                clearScreen();
                cout << GREEN << "Thanks for playing!" << RESET << endl;
                break;
            }
        }
        catch (const exception& e) {
            cout << RED << "Game error: " << e.what() << RESET << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }

        cout << "\nReturning to menu in 3 seconds...\n";
        this_thread::sleep_for(chrono::seconds(3));
    }
}

#ifdef _WIN32
system("chcp 65001 > nul");
#endif


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
