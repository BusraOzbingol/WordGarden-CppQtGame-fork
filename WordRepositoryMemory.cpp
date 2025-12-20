#include "WordRepositoryMemory.h"
#include <cstdlib>
#include <stdexcept>

// Add a word
void WordRepositoryMemory::addWord(const Word& word) {
    words.push_back(word);
}

// Select a random word
Word WordRepositoryMemory::getRandomWord() {
    if (words.empty()) {
        throw std::runtime_error("Word list is empty!");
    }

    int index = rand() % words.size();
    return words[index];
}

// Return all words
std::vector<Word> WordRepositoryMemory::getAllWords() {
    return words;
}
