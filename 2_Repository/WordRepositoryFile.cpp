#include "WordRepositoryFile.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <QString>
#include <QDebug>

/**
 * @brief Constructs the repository and loads words from the specified file.
 * 
 * Seeds the random number generator and calls loadFromFile().
 * 
 * @param file The file path where words are stored.
 */
WordRepositoryFile::WordRepositoryFile(const std::string& file) : filename(file) {
    std::srand(std::time(nullptr)); // Seed random generator
    loadFromFile();                  // Load words from the file
}

/**
 * @brief Loads words from the file into the in-memory list.
 * 
 * Each line in the file should contain a word followed by its category integer.
 * Invalid lines are skipped. Loaded words are printed using qDebug().
 */
void WordRepositoryFile::loadFromFile() {
    words.clear();                   // Clear existing words
    std::ifstream infile(filename);  // Open file for reading
    std::string line;

    while (std::getline(infile, line)) {          // Read line by line
        std::istringstream iss(line);
        std::string wordStr;
        int categoryInt;

        if (!(iss >> wordStr >> categoryInt)) continue; // Skip invalid lines
        qDebug() << "Loaded word:" << QString::fromStdString(wordStr)
                 << "Category:" << categoryInt;
        // Create Word object and add to memory
        words.push_back(Word(wordStr, static_cast<CategoryEnum>(categoryInt)));
    }

    infile.close();  // Close the file
}

/**
 * @brief Saves the in-memory words to the file.
 * 
 * Overwrites the existing file content with the current word list.
 */
void WordRepositoryFile::saveToFile() {
    std::ofstream outfile(filename, std::ios::trunc); // Open file for writing (overwrite)
    for (auto& w : words) {
        outfile << w.getWord() << " " << static_cast<int>(w.getCategory()) << std::endl;
    }
    outfile.close(); // Close the file
}

/**
 * @brief Adds a word to the repository.
 * 
 * Updates the in-memory list and saves changes to the file.
 * 
 * @param word The Word object to add.
 */
void WordRepositoryFile::addWord(const Word& word) {
    words.push_back(word); // Add to memory
    saveToFile();          // Save updated list to file
}
/**
 * @brief Retrieves a random word from the repository.
 * 
 * If the repository is empty, returns a Word with an empty string
 * and category set to Unspecified.
 * 
 * @return A randomly selected Word object from the repository.
 */
Word WordRepositoryFile::getRandomWord() {
    if (words.empty()) 
        return Word("", CategoryEnum::Unspecified); // Return empty if no words

    int index = rand() % words.size();             // Generate random index
    return words[index];                           // Return the randomly selected word
}

/**
 * @brief Returns a copy of all words in the repository.
 * 
 * Provides access to the full list of words currently stored in memory.
 * Modifying the returned vector will not affect the repository.
 * 
 * @return A std::vector containing all Word objects currently stored.
 */
std::vector<Word> WordRepositoryFile::getAllWords() {
    return words; // Return copy of word list
}
