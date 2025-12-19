#include "GameState.h"

GameState::GameState(Word* word, int maxSeconds)
    : m_currentWord(word),
      m_maxTimeSeconds(maxSeconds),
      m_remainingGuesses(6) // Varsayýlan baþlangýç hakký 6 olsun
{
    // Zamanlayýcýlarý (startTime, endTime) varsayýlan (null/invalid) olarak býrakýyoruz
    // veya QDateTime() ile baþlatýyoruz. startTimer() ile aktif hale getirilecek.
}

void GameState::startTimer() {
    m_dateTimeStart = QDateTime::currentDateTime();
    // m_dateTimeEnd'i sýfýrlamak veya geçersiz kýlmak iyi bir uygulamadýr.
    m_dateTimeEnd = QDateTime(); 
}

void GameState::endTimer() {
    m_dateTimeEnd = QDateTime::currentDateTime();
}

int GameState::getElapsedTime() const {
    if (m_dateTimeStart.isNull()) return 0;
    QDateTime end = m_dateTimeEnd.isNull() ? QDateTime::currentDateTime() : m_dateTimeEnd;
    return static_cast<int>(m_dateTimeStart.msecsTo(end) / 1000);
}

QString GameState::getCurrentWordDisplayText() const {
    if (!m_currentWord) return "";
    return QString::fromStdString(m_currentWord->getWord());
}
    
   


void GameState::decreaseRemainingGuesses() {
    if (m_remainingGuesses > 0) {
        m_remainingGuesses--;
    }
}
bool GameState::isGameWon() const {
    // Kelime nesnesine sorarak kontrol et
    return m_currentWord->isGuessed();
}

bool GameState::isGameOver() const {
    // Oyunun bitmesi için 3 koþuldan birinin gerçekleþmesi gerekir:
    
    // 1. Kazanýldý mý?
    if (isGameWon()) {
        return true;
    }

    // 2. Tahmin hakký bitti mi?
    if (m_remainingGuesses <= 0) {
        return true;
    }

    // 3. Süre aþýldý mý? (Eðer bir zaman sýnýrý varsa)
    if (m_maxTimeSeconds > 0 && getElapsedTime() >= m_maxTimeSeconds) {
        return true;
    }

    return false;
}

Word* GameState::getCurrentWord() const { return m_currentWord; }
int GameState::getRemainingGuesses() const { return m_remainingGuesses; }
int GameState::getMaxTimeSeconds() const { return m_maxTimeSeconds; }
