#pragma once
#include <string>
#include "Word.h"
#include "WordRepository.h"
using namespace std;

class WordManager {
private:
    WordRepository* repository;   // Word repository
    Word* currentWord;            // Current game word
    int score;                    // Game score
    int maxWrongGuesses;          // Maximum allowed wrong guesses

public:
    // Constructor
    WordManager(WordRepository* repository);

    // Start a new game
    void startNewGame(string categoryName);

    // Make a letter guess
    void makeGuess(char letter);

    // Return the masked version of the word
    string getMaskedWord();

    // Return remaining number of guesses
    int getRemainingGuesses();

    // Check if the game is over
    bool isGameOver();

    // Check if the game is won
    bool isGameWon();

    // Update the score
    void updateScore(int scoreChange);

    // Return the score
    int getScore();
};
