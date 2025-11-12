#include "Battleship.h"
#include "connectfour.h"
#include "Leaderboard.h"
#include "minesweeper.h"
#include "tictactoe.h" 
#include "wordle.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <string>
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

        if (!(cin >> choice)) {
            cout << RED << "Invalid input. Please enter a number (1-3).\n" << RESET;
            cin.clear();
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }

        if (choice == 1) {
            clearScreen();

            string logo[] = {
                "██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗",
                "██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗",
                "██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██║  ██║",
                "██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██████║",
                "██║  ██║██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██╔╝",
                "██████╗╝╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝██╝ ",
                "╚═════╝                                                              ╚═╝ "
            };
            gameIntro(logo, 7);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            Game* game = new Battleship(playerName);
            game->start();
            delete game;

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 2) {
            clearScreen();

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
            gameIntro(logo, 8);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            Game* game = new Connect4(playerName);
            game->start();
            delete game;

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 3) {
            clearScreen();

            string logo[] = {
                " ___ ___  ____  ____     ___  _____ __    __    ___    ___  ____    ___  ____  ",
                "|   T   Tl    j|    \\   /  _]/ ___/|  T__T  T  /  _]  /  _]|    \\  /  _]|    \\ ",
                "| _   _ | |  T |  _  Y /  [_(   \\_ |  |  |  | /  [_  /  [_ |  o  )/  [_ |  D  )",
                "|  \\_/  | |  | |  |  |Y    _]\\__  T|  |  |  |Y    _]Y    _]|   _/Y    _]|    / ",
                "|   |   | |  | |  |  ||   [_ /  \\ |l  `  '  !|   [_ |   [_ |  |  |   [_ |    \\ ",
                "|   |   | j  l |  |  ||     T\\    | \\      / |     T|     T|  |  |     T|  .  Y",
                "l___j___j|____jl__j__jl_____j \\___j  \\_/\\_/  l_____jl_____jl__j  l_____jl__j\\_j"
            };
            gameIntro(logo, 7);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            Game* game = new Minesweeper(9, 9, 10, playerName);
            game->start();
            delete game;

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 4) {
            clearScreen();

            string logo[] = {
            " __      __                .___.__          ",
            "/  \\    /  \\___________  __| _/|  |   ____  ",
            "\\   \\/\\/   /  _ \\_  __ \\/ __ | |  | _/ __ \\ ",
            " \\        (  <_> )  | \\/ /_/ | |  |_\\  ___/ ",
            "  \\__/\\  / \\____/|__|  \\____ | |____/\\___  >",
            "       \\/                   \\/           \\/ ",
            };
            gameIntro(logo, 6);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            Game* game = new Wordle(playerName);
            game->start();
            delete game;

            cout << "\nReturning to main menu in 3 seconds...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        else if (choice == 5) {
            clearScreen();
            string logo[] = {
            " _______ _______ ______       _______ _______ ______       _______ _______ _______ ",
            "|_     _|_     _|      |_____|_     _|   _   |      |_____|_     _|       |    ___|",
            "  |   |  _|   |_|   ---|______||   | |       |   ---|______||   | |   -   |    ___|",
            "  |___| |_______|______|       |___| |___|___|______|       |___| |_______|_______|",

            };
            gameIntro(logo, 4);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string playerName;
            cout << CYAN << "\nEnter your name: " << RESET;
            getline(cin, playerName);

            Game* game = new Tictactoe(playerName);
            game->start();
            delete game;

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
    mainMenu();
    return 0;
}
