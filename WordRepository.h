#pragma once
#include <vector>
#include "Word.h"
using namespace std;

class WordRepository {
private:
    vector<Word> words;  // Kelime listesi

public:
    WordRepository() = default;

    // Yeni kelime ekle
    void addWord(const Word& word);

    // Rastgele bir kelime döndür
    Word getRandomWord();

    // Tüm kelimeleri döndür (isteğe bağlı)
    vector<Word> getAllWords();
};
