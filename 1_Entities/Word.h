#ifndef WORD_H
#define WORD_H

#include <string>
#include <set>
#include "0_Enums/CategoryEnum.h"

/**
 * @class Word
 * @brief Represents a word that can be guessed letter by letter.
 * 
 * This class stores a word, its category, guessed letters,
 * number of incorrect guesses, and completion status.
 */
class Word {
private:
    /** The actual word to be guessed */
    std::string word;

    /** Category of the word */
    CategoryEnum category;

    /** Number of incorrect letter guesses */
    int incorrectGuesses;

    /** Indicates whether the word has been fully guessed */
    bool guessed;

    /** Set of letters that have already been guessed */
    std::set<char> guessedLetters;

public:
    /**
     * @brief Constructs a Word object.
     * 
     * @param word The word to be guessed.
     * @param category The category of the word.
     */
    Word(std::string word, CategoryEnum category);

    /**
     * @brief Returns the word.
     * 
     * @return The word as a string.
     */
    std::string getWord();

    /**
     * @brief Returns the category of the word.
     * 
     * @return The word category.
     */
    CategoryEnum getCategory();

    /**
     * @brief Attempts to guess a letter in the word.
     * 
     * @param letter The letter to guess.
     * @return true if the letter exists in the word, false otherwise.
     */
    bool guessLetter(char letter);

    /**
     * @brief Checks if the word has been completely guessed.
     * 
     * @return true if the word is fully guessed, false otherwise.
     */
    bool isGuessed();

    /**
     * @brief Returns the number of incorrect guesses.
     * 
     * @return Number of incorrect guesses.
     */
    int getIncorrectGuesses();

    /**
     * @brief Sets the guessed state of the word.
     * 
     * @param guessed New guessed state.
     */
    void setGuessed(bool guessed);

    /**
     * @brief Checks whether a letter has already been guessed.
     * 
     * @param letter The letter to check.
     * @return true if the letter was guessed before, false otherwise.
     */
    bool isLetterGuessed(char letter);

    /**
     * @brief Calculates the percentage of correctly guessed letters.
     * 
     * @return Completion percentage (0–100).
     */
    double getCompletionPercentage();
};

#endif
