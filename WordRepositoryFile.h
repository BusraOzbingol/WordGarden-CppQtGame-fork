#pragma once
#include "IWordRepository.h"
#include "Word.h"
#include <vector>
#include <string>

// File-based implementation of IWordRepository
class WordRepositoryFile : public IWordRepository {
private:
    std::string filename;           // The file where words are stored
    std::vector<Word> words;       // In-memory list of words

    void loadFromFile();           // Load words from the file into memory
    void saveToFile();             // Save memory words to the file

public:
    // Constructor: receives file name and loads words from it
    WordRepositoryFile(const std::string& file);

    // Interface implementation
    void addWord(const Word& word) override;       // Add a word to the repository
    Word getRandomWord() override;                 // Get a random word
    std::vector<Word> getAllWords() override;     // Get all words
};
