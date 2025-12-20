#pragma once
#include <string>
#include "Word.h"
#include "IWordRepository.h"
#include "CategoryEnum.h"
using namespace std;

class WordManager {
private:
    IWordRepository* repository;  // Word repository
    Word* currentWord;            // Current game word
    int score;                    // Game score
    int maxWrongGuesses;          // Maximum allowed wrong guesses


public:
    // Constructor
    WordManager(IWordRepository* repository);

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
    Word* getCurrentWord();

};
