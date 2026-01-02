#include "3_Manager/WordManager.h"
#include "2_Repository/IWordRepository.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <unordered_set>
#include <iostream>
using namespace std;

/**
 * @brief Constructs a WordManager with a given word repository.
 * 
 * @param repository Pointer to an IWordRepository implementation.
 */
WordManager::WordManager(IWordRepository* repository)
    : repository(repository), currentWord(nullptr), score(0) {}

/** 
 * @brief Set of words already used in the game.
 * @details Keeps track of words to avoid repetition.
 */
unordered_set<string> usedWords;

/**
 * @brief Marks a word as used in the game.
 * 
 * @param word Pointer to the Word to mark as used.
 */
void WordManager::markWordAsUsed(Word* word) {
    if(word != nullptr) {
        usedWords.insert(word->getWord());
    }
}

/**
 * @brief Checks if a word has already been used.
 * 
 * @param word The word to check.
 * @return true if the word was used before, false otherwise.
 */
bool WordManager::isWordUsed(const std::string& word) {
    return usedWords.count(word) > 0;
}

/**
 * @brief Starts a new game by selecting a word from the given category.
 * 
 * @param categoryName Name of the category.
 * @details Filters out words already used. Randomly selects a word from the remaining ones.
 */
void WordManager::startNewGame(string categoryName) {
    vector<Word> filteredWords;

    for (Word w : repository->getAllWords()) {
        if (
            ((categoryName == "Animals" && w.getCategory() == CategoryEnum::Animals) ||
             (categoryName == "Plants" && w.getCategory() == CategoryEnum::Plants) ||
             (categoryName == "Technology" && w.getCategory() == CategoryEnum::Technology) ||
             (categoryName == "Cities" && w.getCategory() == CategoryEnum::Cities) ||
             (categoryName == "Jobs" && w.getCategory() == CategoryEnum::Jobs) ||
             (categoryName == "Movies" && w.getCategory() == CategoryEnum::Movies))
            && !isWordUsed(w.getWord())
           )
        {
            filteredWords.push_back(w);
        }
    }

    if (filteredWords.empty()) return;

    srand(time(nullptr));
    int index = rand() % filteredWords.size();
    currentWord = new Word(filteredWords[index]);
}

/**
 * @brief Returns the current Word object.
 * 
 * @return Pointer to the current Word, or nullptr if no game started.
 */
Word* WordManager::getCurrentWord() {
    return currentWord;
}

/**
 * @brief Makes a letter guess for the current word.
 * 
 * @param letter The guessed letter.
 * @return true if the letter exists in the word, false otherwise.
 * @details Updates score: +5 for correct, -2 for incorrect guesses.
 */
bool WordManager::makeGuess(char letter) {
    if (currentWord == nullptr) return false;

    bool correct = currentWord->guessLetter(letter);
    if (correct) {
        updateScore(5);
    } else {
        updateScore(-2);
    }
    return correct;
}

/**
 * @brief Returns the masked version of the current word.
 * 
 * @return String with unguessed letters replaced by underscores.
 */
string WordManager::getMaskedWord() {
    if (currentWord == nullptr) return "";

    string masked = "";
    for (char c : currentWord->getWord()) {
        if (currentWord->isLetterGuessed(c)) {
            masked += c;
        } else {
            masked += '_';
        }
    }
    return masked;
}

/**
 * @brief Checks if the current game is won.
 * 
 * @return true if all letters have been guessed, false otherwise.
 */
bool WordManager::isGameWon() {
    if (currentWord == nullptr) return false;
    return currentWord->isGuessed();
}

/**
 * @brief Handles logic when the game is won.
 * 
 * Marks the current word as used to prevent repetition.
 */
void WordManager::onGameWon() {
    if (currentWord != nullptr) {
        markWordAsUsed(currentWord);
    }
}

/**
 * @brief Updates the player's score.
 * 
 * @param scoreChange Amount to add (or subtract) from the current score.
 */
void WordManager::updateScore(int scoreChange) {
    score += scoreChange;
}

/**
 * @brief Returns the current game score.
 * 
 * @return Integer representing the player's score.
 */
int WordManager::getScore() {
    return score;
}
