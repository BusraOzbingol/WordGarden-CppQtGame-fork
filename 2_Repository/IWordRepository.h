#pragma once
#include <vector>
#include "1_Entities/Word.h"

/**
 * @class IWordRepository
 * @brief Interface for a word repository.
 * 
 * This interface defines methods for storing, retrieving, 
 * and accessing words in a repository.
 */
class IWordRepository {
public:
    /** Virtual destructor */
    virtual ~IWordRepository() = default;

    /**
     * @brief Adds a word to the repository.
     * 
     * @param word The Word object to add.
     */
    virtual void addWord(const Word& word) = 0;

    /**
     * @brief Retrieves a random word from the repository.
     * 
     * @return A randomly selected Word object.
     */
    virtual Word getRandomWord() = 0;

    /**
     * @brief Retrieves all words in the repository.
     * 
     * @return A vector containing all Word objects.
     */
    virtual std::vector<Word> getAllWords() = 0;
};
