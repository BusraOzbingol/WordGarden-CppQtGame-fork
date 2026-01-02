#include "1_Entities/Word.h"
#include <cctype>
#include <set>
#include <string>

#include "0_Enums/CategoryEnum.h"

using namespace std;

/**
 * @brief Constructs a Word object with a given word and category.
 * 
 * @param word The word to be guessed.
 * @param category The category of the word.
 */
Word::Word(string word, CategoryEnum category)
    : word(word), category(category), incorrectGuesses(0), guessed(false) {}

/**
 * @brief Returns the actual word.
 * 
 * @return The word as a string.
 */
string Word::getWord() {
    return word;
}

/**
 * @brief Returns the category of the word.
 * 
 * @return CategoryEnum value representing the word category.
 */
CategoryEnum Word::getCategory() {
    return category;
}

/**
 * @brief Tries to guess a letter in the word.
 * 
 * The letter is converted to lowercase and stored in the guessed letters set.
 * If the letter does not exist in the word, incorrect guess count is increased.
 * If all letters are guessed correctly, the word is marked as guessed.
 * 
 * @param letter The letter to guess.
 * @return true if the letter exists in the word, false otherwise.
 */
bool Word::guessLetter(char letter) {
    letter = tolower(letter);
    guessedLetters.insert(letter);

    bool correct = false;
    for (char c : word) {
        if (tolower(c) == letter) {
            correct = true;
            break;
        }
    }

    if (!correct) {
        incorrectGuesses++;
        return false;
    }

    bool allGuessed = true;
    for (char c : word) {
        if (guessedLetters.find(tolower(c)) == guessedLetters.end()) {
            allGuessed = false;
            break;
        }
    }

    guessed = allGuessed;
    return true;
}

/**
 * @brief Checks whether the word has been completely guessed.
 * 
 * @return true if the word is guessed, false otherwise.
 */
bool Word::isGuessed() {
    return guessed;
}

/**
 * @brief Returns the number of incorrect guesses.
 * 
 * @return Number of incorrect guesses.
 */
int Word::getIncorrectGuesses() {
    return incorrectGuesses;
}

/**
 * @brief Manually sets the guessed state of the word.
 * 
 * @param guessed Boolean value to set guessed status.
 */
void Word::setGuessed(bool guessed) {
    this->guessed = guessed;
}

/**
 * @brief Checks if a specific letter has already been guessed.
 * 
 * @param letter The letter to check.
 * @return true if the letter was guessed before, false otherwise.
 */
bool Word::isLetterGuessed(char letter) {
    return guessedLetters.count(tolower(letter)) > 0;
}

/**
 * @brief Calculates the completion percentage of the word.
 * 
 * The percentage is based on how many letters of the word
 * have been correctly guessed.
 * 
 * @return Completion percentage between 0 and 100.
 */
double Word::getCompletionPercentage() {
    if (word.empty()) return 0.0;

    int total = word.size();
    int correct = 0;

    for (char c : word) {
        if (guessedLetters.count(tolower(c)) > 0) {
            correct++;
        }
    }

    return (correct * 100.0) / total;
}
