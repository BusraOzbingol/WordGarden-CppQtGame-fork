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
    // Eðer zamanlayýcý baþlatýlmadýysa veya durdurulmadýysa süre hesaplamasý farklý yapýlýr.
    if (m_dateTimeStart.isNull()) {
        return 0;
    }
    
    QDateTime end = m_dateTimeEnd.isNull() ? QDateTime::currentDateTime() : m_dateTimeEnd;
    
    // msecsTo() metodu ile iki zaman arasýndaki fark milisaniye cinsinden bulunur.
    qint64 msDiff = m_dateTimeStart.msecsTo(end); 
    
    return static_cast<int>(msDiff / 1000); // Saniye cinsine çevir.
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
