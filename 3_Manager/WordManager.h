#pragma once
#include <string>
#include <unordered_set> 
#include "../1_Entities/Word.h"
#include "../2_Repository/IWordRepository.h"
#include "../0_Enums/CategoryEnum.h"

using namespace std;

/**
 * @class WordManager
 * @brief Manages the game logic for word guessing.
 * 
 * This class handles interactions between the game and the word repository,
 * including selecting words, tracking score, checking guesses, and managing used words.
 */
class WordManager {
private:
    /** Pointer to the word repository */
    IWordRepository* repository;

    /** Pointer to the current word in the game */
    Word* currentWord;

    /** Current game score */
    int score;

    /** Set of words already used in the game */
    unordered_set<std::string> usedWords;

public:
    /**
     * @brief Constructs the WordManager with a repository.
     * 
     * @param repository Pointer to an IWordRepository implementation.
     */
    WordManager(IWordRepository* repository);

    /**
     * @brief Starts a new game with a given category.
     * 
     * @param categoryName Name of the category to select a word from.
     */
    void startNewGame(string categoryName);

    /**
     * @brief Makes a letter guess for the current word.
     * 
     * @param letter The guessed letter.
     * @return true if the letter exists in the word, false otherwise.
     * @note This is a newly added method returning a boolean indicating guess success.
     */
    bool makeGuess(char letter);

    /**
     * @brief Returns the masked version of the current word.
     * 
     * @return A string with unguessed letters masked.
     */
    string getMaskedWord();

    /**
     * @brief Checks if the current game is won.
     * 
     * @return true if the word is completely guessed, false otherwise.
     */
    bool isGameWon();

    /**
     * @brief Updates the game score.
     * 
     * @param scoreChange Amount to add (or subtract) from the current score.
     */
    void updateScore(int scoreChange);

    /**
     * @brief Returns the current game score.
     * 
     * @return Current score as an integer.
     */
    int getScore();

    /**
     * @brief Returns the current Word object.
     * 
     * @return Pointer to the current Word.
     */
    Word* getCurrentWord();

    /**
     * @brief Marks a word as used in the game.
     * 
     * @param word Pointer to the Word to mark as used.
     */
    void markWordAsUsed(Word* word);

    /**
     * @brief Checks if a word has already been used in the game.
     * 
     * @param word The word to check.
     * @return true if the word was used before, false otherwise.
     */
    bool isWordUsed(const std::string& word);

    /**
     * @brief Handles logic when the game is won.
     * 
     * Could be used to update score, mark words as used, or trigger events.
     */
    void onGameWon();
};
