#include "WordRepository.h"
#include <cstdlib>
#include <ctime>

// Kelime ekle
void WordRepository::addWord(const Word& word) {
    words.push_back(word);
}

// Rastgele kelime seç
Word WordRepository::getRandomWord() {
    if (words.empty()) {
        throw runtime_error("Kelime listesi boş!");
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    int index = rand() % words.size();
    return words[index];
}

// Tüm kelimeleri döndür
vector<Word> WordRepository::getAllWords() {
    return words;
}
