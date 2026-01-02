#pragma once

#include "2_Repository/IWordRepository.h"
#include "1_Entities/Word.h"
#include <vector>

/**
 * @class WordRepositoryMemory
 * @brief In-memory implementation of IWordRepository.
 * 
 * @details
 * This class stores words only in memory and does not persist them to a file.
 * Currently, it may not be actively used in the project, but it provides a 
 * dynamic repository option. 
 * 
 * In the future, this can be useful when adding words dynamically during runtime 
 * instead of relying on a text file, e.g., for testing, user input, or temporary sessions.
 */
class WordRepositoryMemory : public IWordRepository {
private:
    /** In-memory list of words */
    std::vector<Word> words;

public:
    /** Default constructor */
    WordRepositoryMemory() = default;

    /**
     * @brief Adds a word to the in-memory repository.
     * 
     * @param word The Word object to add.
     */
    void addWord(const Word& word) override;

    /**
     * @brief Retrieves a random word from the in-memory repository.
     * 
     * @return A randomly selected Word object.
     */
    Word getRandomWord() override;

    /**
     * @brief Returns all words in the in-memory repository.
     * 
     * @return A vector containing all Word objects.
     */
    std::vector<Word> getAllWords() override;
};
