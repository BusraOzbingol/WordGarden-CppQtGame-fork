#pragma once
#include <vector>
#include "Word.h"
using namespace std;

class WordRepository {
private:
    vector<Word> words;  // Word list

public:
    WordRepository() = default;

    // Add a new word
    void addWord(const Word& word);

    // Return a random word
    Word getRandomWord();

    // Return all words (optional)
    vector<Word> getAllWords();
};
