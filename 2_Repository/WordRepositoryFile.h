#pragma once
#include "2_Repository/IWordRepository.h"
#include "1_Entities/Word.h"
#include <vector>
#include <string>

/**
 * @class WordRepositoryFile
 * @brief File-based implementation of IWordRepository.
 * 
 * This class manages words stored in a file. It loads words into memory 
 * at startup and saves changes back to the file.
 */
class WordRepositoryFile : public IWordRepository {
private:
    /** The file where words are stored */
    std::string filename;

    /** In-memory list of words */
    std::vector<Word> words;

    /**
     * @brief Loads words from the file into memory.
     */
    void loadFromFile();

    /**
     * @brief Saves the in-memory words back to the file.
     */
    void saveToFile();

public:
    /**
     * @brief Constructs the repository with a given file.
     * 
     * @param file The file path where words are stored.
     */
    WordRepositoryFile(const std::string& file);

    /**
     * @brief Adds a word to the repository.
     * 
     * This updates the in-memory list and saves the change to the file.
     * 
     * @param word The Word object to add.
     */
    void addWord(const Word& word) override;

    /**
     * @brief Retrieves a random word from the repository.
     * 
     * @return A randomly selected Word object.
     */
    Word getRandomWord() override;

    /**
     * @brief Returns all words in the repository.
     * 
     * @return A vector containing all Word objects.
     */
    std::vector<Word> getAllWords() override;
};
