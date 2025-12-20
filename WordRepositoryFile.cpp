#include "WordRepositoryFile.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

// Constructor: load words from file
WordRepositoryFile::WordRepositoryFile(const std::string& file) : filename(file) {
    std::srand(std::time(nullptr)); // Seed random generator
    loadFromFile();                  // Load words from the file
}

// Load words from file
void WordRepositoryFile::loadFromFile() {
    words.clear();                   // Clear existing words
    std::ifstream infile(filename);  // Open file for reading
    std::string line;

    while (std::getline(infile, line)) {          // Read line by line
        std::istringstream iss(line);
        std::string wordStr;
        int categoryInt;

        if (!(iss >> wordStr >> categoryInt)) continue; // Skip invalid lines

        // Create Word object and add to memory
        words.push_back(Word(wordStr, static_cast<CategoryEnum>(categoryInt)));
    }

    infile.close();  // Close the file
}

// Save words to file
void WordRepositoryFile::saveToFile() {
    std::ofstream outfile(filename, std::ios::trunc); // Open file for writing (overwrite)
    for (auto& w : words) {
        outfile << w.getWord() << " " << static_cast<int>(w.getCategory()) << std::endl;
    }
    outfile.close(); // Close the file
}

// Add a word to repository
void WordRepositoryFile::addWord(const Word& word) {
    words.push_back(word); // Add to memory
    saveToFile();          // Save updated list to file
}

// Get a random word
Word WordRepositoryFile::getRandomWord() {
    if (words.empty()) return Word("", CategoryEnum::Unspecified); // Return empty if no words
    int index = rand() % words.size();                         // Random index
    return words[index];                                       // Return word
}

// Get all words
std::vector<Word> WordRepositoryFile::getAllWords() {
    return words; // Return copy of word list
}
