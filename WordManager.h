#pragma once
#include <string>
#include "Word.h"
#include "WordRepository.h"
using namespace std;

class WordManager {
private:
    WordRepository* repository;   // Kelime deposu
    Word* currentWord;            // O anki oyun kelimesi
    int score;                    // Oyun skoru
    int maxWrongGuesses;          // Maksimum yanlış tahmin hakkı

public:
    // Constructor
    WordManager(WordRepository* repository);

    // Yeni oyun başlat
    void startNewGame(string categoryName);

    // Harf tahmini yap
    void makeGuess(char letter);

    // Kelimenin maskelenmiş hâlini döndür
    string getMaskedWord();

    // Kalan tahmin hakkını döndür
    int getRemainingGuesses();

    // Oyun bitti mi?
    bool isGameOver();

    // Oyun kazanıldı mı?
    bool isGameWon();

    // Skoru güncelle
    void updateScore(int scoreChange);

    // Skoru döndür
    int getScore();
};
