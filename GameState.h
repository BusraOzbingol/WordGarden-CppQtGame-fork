#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Word.h"
#include <QDateTime> // Zaman yönetimi için gerekli
#include <QString>

class GameState {
public:
    // Yapýcý metot
    GameState(Word* word, int maxSeconds);

    // Zamanlayýcý Metotlarý
    void startTimer();
    void endTimer();
    int getElapsedTime() const; // Saniye cinsinden geçen süre

    // Durum Kontrol Metotlarý
    bool isGameWon() const;
    bool isGameOver() const; // Oyun Bitti mi?
    
    // Getter'lar
    Word* getCurrentWord() const;
    int getRemainingGuesses() const;
    int getMaxTimeSeconds() const;
    
    // std::string'i GUI için QString'e çevirir
	    QString getCurrentWordDisplayText() const;

    // Tahmin hakkýný azaltmak için harici metot (GameStateManager tarafýndan kullanýlacak)
    void decreaseRemainingGuesses();

private:
    Word* m_currentWord;
    int m_remainingGuesses; // Yanlýþ tahmin hakký (Örn: 6 yaprak)
    QDateTime m_dateTimeStart;
    QDateTime m_dateTimeEnd;
    int m_maxTimeSeconds; // Maksimum oynama süresi
};
#endif
