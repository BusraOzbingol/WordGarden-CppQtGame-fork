#include "WordRepository.h"
#include <cstdlib>
#include <ctime>

// Add a word
void WordRepository::addWord(const Word& word) {
    words.push_back(word);
}

// Select a random word
Word WordRepository::getRandomWord() {
    if (words.empty()) {
        throw runtime_error("Word list is empty!");
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    int index = rand() % words.size();
    return words[index];
}

// Return all words
vector<Word> WordRepository::getAllWords() {
    return words;
}
