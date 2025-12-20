#pragma once

#include "IWordRepository.h"
#include "Word.h"
#include <vector>

class WordRepositoryMemory : public IWordRepository {
private:
    std::vector<Word> words;

public:
    WordRepositoryMemory() = default;

    void addWord(const Word& word) override;
    Word getRandomWord() override;
    std::vector<Word> getAllWords() override;
};
