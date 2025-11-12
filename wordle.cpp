#include "Wordle.h"
#include <thread>
#include <chrono>
#include <limits>

using namespace std;


#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define GRAY    "\033[90m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"


#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif


Wordle::Wordle(string playerName)
    : Game("Wordle", playerName, 0), gameOver(false) {
    reset();
}


void Wordle::generateSecret() {
    vector<string> words;
    ifstream file("wordle.txt");

    if (file.is_open()) {
        string word;
        while (file >> word) {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            if (word.size() == WORD_LENGTH)
                words.push_back(word);
        }
        file.close();
    }
    secretWord = words[rand() % words.size()];
}


string Wordle::toUpper(string s) const {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}


void Wordle::reset() {
    srand(time(nullptr));
    generateSecret();
    guesses.clear();
    gameOver = false;
}


void Wordle::showRules() {
    cout << YELLOW << "\nWORDLE RULES:\n" << RESET;
    cout << "1. Guess the 5-letter secret word within 6 tries.\n";
    cout << "2. Letters turn " << GREEN << "green" << RESET << " if correct and in the right position.\n";
    cout << "3. Letters turn " << YELLOW << "yellow" << RESET << " if correct but in the wrong position.\n";
    cout << "4. Gray letters mean they don't exist in the word.\n";
    cout << "\nPress ENTER to continue...";
    cin.get();
}


void Wordle::display() const {
    system(CLEAR_CMD);
    cout << CYAN << "\n===== WORDLE =====" << RESET << endl;
    cout << "Secret Word: (hidden)\n";

    for (int i = 0; i < MAX_ATTEMPTS; ++i) {
        if (i < (int)guesses.size()) {
            string guess = guesses[i];
            for (int j = 0; j < WORD_LENGTH; ++j) {
                char g = guess[j];
                if (g == secretWord[j])
                    cout << GREEN <<" "<< g << " " << RESET;
                else if (secretWord.find(g) != string::npos)
                    cout << YELLOW <<" "<< g << " " << RESET;
                else
                    cout << GRAY <<" "<< g << " " << RESET;
            }
        } else {
            for (int j = 0; j < WORD_LENGTH; ++j) cout << " _ ";
        }
        cout << endl;
    }
    cout << endl;
}



void Wordle::start() {
    showRules();
    for (int attempt = 0; attempt < MAX_ATTEMPTS && !gameOver; ++attempt) {
        display();
        cout << YELLOW << "Attempt " << attempt + 1 << "/" << MAX_ATTEMPTS << RESET << endl;
        cout << "Enter your guess: ";
        string guess; cin >> guess;
        guess = toUpper(guess);

        if (guess.size() != WORD_LENGTH) {
            cout << RED << "Word must be 5 letters!\n" << RESET;
            this_thread::sleep_for(chrono::milliseconds(800));
            attempt--;
            continue;
        }

        guesses.push_back(guess);

        if (guess == secretWord) {
            display();
            cout << GREEN << "\n🎉 You guessed the word! " << secretWord << RESET << endl;
            player += 50;
            Leaderboard lb(gameName);
            lb = lb + player;
            cout << CYAN << "\n📊 Current " << gameName << " Leaderboard:\n" << RESET;
            cout << lb;
            gameOver = true;
            return;
        }
    }

    display();
    cout << RED << "\n💀 Out of attempts! The word was: " << secretWord << RESET << endl;
    Leaderboard lb(gameName);
    lb = lb + player;
    cout << CYAN << "\n📊 Current " << gameName << " Leaderboard:\n" << RESET;
    cout << lb;
}
