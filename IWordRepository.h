#pragma once
#include <vector>
#include "Word.h"

class IWordRepository {
public:
    virtual ~IWordRepository() = default;

    virtual void addWord(const Word& word) = 0;
    virtual Word getRandomWord() = 0;
    virtual std::vector<Word> getAllWords() = 0;
};
