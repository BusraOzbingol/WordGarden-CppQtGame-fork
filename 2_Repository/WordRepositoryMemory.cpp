#include "2_Repository/WordRepositoryMemory.h"
#include <cstdlib>
#include <stdexcept>

/**
 * @brief Adds a word to the in-memory repository.
 * 
 * @param word The Word object to add.
 * @details
 * This repository only stores words in memory and does not persist them.
 * Useful for dynamic word addition at runtime, for testing, or temporary sessions.
 */
void WordRepositoryMemory::addWord(const Word& word) {
    words.push_back(word);
}

/**
 * @brief Selects a random word from the in-memory repository.
 * 
 * @return A randomly selected Word object.
 * @throws std::runtime_error if the word list is empty.
 * @details
 * Since this repository is in-memory, it provides quick access to words
 * without reading from a file. Ideal for scenarios where words are
 * dynamically generated or temporarily stored.
 */
Word WordRepositoryMemory::getRandomWord() {
    if (words.empty()) {
        throw std::runtime_error("Word list is empty!");
    }

    int index = rand() % words.size();
    return words[index];
}

/**
 * @brief Returns all words stored in memory.
 * 
 * @return A vector containing all Word objects.
 * @details
 * This allows inspection of all dynamically added words. 
 * The list is volatile and will be lost when the program ends.
 */
std::vector<Word> WordRepositoryMemory::getAllWords() {
    return words;
}
