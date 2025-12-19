#include "WordManager.h"
#include <algorithm>
#include <random>
#include <ctime>

WordManager::WordManager(WordRepository* repository)
    : repository(repository), currentWord(nullptr), score(0), maxWrongGuesses(6) {}

// Yeni oyun başlat
void WordManager::startNewGame(string categoryName) {
    vector<Word> filteredWords;

    // Kategoriye göre filtrele
    for (Word w : repository->getAllWords()) {
        if ((categoryName == "Animals" && w.getCategory() == Animals) ||
            (categoryName == "Plants" && w.getCategory() == Plants) ||
            (categoryName == "Objects" && w.getCategory() == Objects)) {
            filteredWords.push_back(w);
        }
    }

    if (filteredWords.empty()) return;

    // Rastgele kelime seç
    srand(time(nullptr));
    int index = rand() % filteredWords.size();
    currentWord = new Word(filteredWords[index]);
}

// Harf tahmini
void WordManager::makeGuess(char letter) {
    if (currentWord == nullptr) return;

    bool correct = currentWord->guessLetter(letter);
    if (correct) {
        updateScore(5);  // doğru tahmin +5 puan
    } else {
        updateScore(-2); // yanlış tahmin -2 puan
    }
}

// Maskeli kelime döndür
string WordManager::getMaskedWord() {
    if (currentWord == nullptr) return "";

    string masked = "";
    for (char c : currentWord->getWord()) {
        if (currentWord->isLetterGuessed(c)) { // isLetterGuessed fonksiyonu Word içinde olmalı
            masked += c;
        } else {
            masked += '_';
        }
    }
    return masked;
}

// Kalan tahmin hakkı
int WordManager::getRemainingGuesses() {
    if (currentWord == nullptr) return 0;
    return maxWrongGuesses - currentWord->getIncorrectGuesses();
}

// Oyun bitti mi?
bool WordManager::isGameOver() {
    if (currentWord == nullptr) return true;
    return isGameWon() || getRemainingGuesses() <= 0;
}

// Oyun kazanıldı mı?
bool WordManager::isGameWon() {
    if (currentWord == nullptr) return false;
    return currentWord->isGuessed();
}

// Skoru güncelle
void WordManager::updateScore(int scoreChange) {
    score += scoreChange;
}

// Skoru döndür
int WordManager::getScore() {
    return score;
}
