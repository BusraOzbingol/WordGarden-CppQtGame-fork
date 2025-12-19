#include "WordManager.h"
#include <algorithm>
#include <random>
#include <ctime>

WordManager::WordManager(WordRepository* repository)
    : repository(repository), currentWord(nullptr), score(0), maxWrongGuesses(6) {}

// Start a new game
void WordManager::startNewGame(string categoryName) {
    vector<Word> filteredWords;

    // Filter words by category
    for (Word w : repository->getAllWords()) {
        if ((categoryName == "Animals" && w.getCategory() == Animals) ||
            (categoryName == "Plants" && w.getCategory() == Plants) ||
            (categoryName == "Objects" && w.getCategory() == Objects)) {
            filteredWords.push_back(w);
        }
    }

    if (filteredWords.empty()) return;

    // Select a random word
    srand(time(nullptr));
    int index = rand() % filteredWords.size();
    currentWord = new Word(filteredWords[index]);
}

// Make a letter guess
void WordManager::makeGuess(char letter) {
    if (currentWord == nullptr) return;

    bool correct = currentWord->guessLetter(letter);
    if (correct) {
        updateScore(5);   // correct guess +5 points
    } else {
        updateScore(-2);  // wrong guess -2 points
    }
}

// Return the masked word
string WordManager::getMaskedWord() {
    if (currentWord == nullptr) return "";

    string masked = "";
    for (char c : currentWord->getWord()) {
        if (currentWord->isLetterGuessed(c)) { // isLetterGuessed must exist in Word
            masked += c;
        } else {
            masked += '_';
        }
    }
    return masked;
}

// Remaining number of guesses
int WordManager::getRemainingGuesses() {
    if (currentWord == nullptr) return 0;
    return maxWrongGuesses - currentWord->getIncorrectGuesses();
}

// Check if the game is over
bool WordManager::isGameOver() {
    if (currentWord == nullptr) return true;
    return isGameWon() || getRemainingGuesses() <= 0;
}

// Check if the game is won
bool WordManager::isGameWon() {
    if (currentWord == nullptr) return false;
    return currentWord->isGuessed();
}

// Update score
void WordManager::updateScore(int scoreChange) {
    score += scoreChange;
}

// Get current score
int WordManager::getScore() {
    return score;
}
