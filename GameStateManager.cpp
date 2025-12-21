#include "GameStateManager.h"
#include <QDebug>

GameStateManager::GameStateManager(GameStateRepository* repository, WordManager* wordManager)
    : m_repository(repository), m_wordManager(wordManager), m_currentGameState(nullptr) 
{
    // Program açýldýðýnda otomatik olarak son kaydý yüklemeye çalýþýr
    loadLastGame(); 
}

GameStateManager::~GameStateManager() {
    // Aktif bir oyun varsa ve kaydedilmemiþse burada yönetilebilir
    // m_currentGameState pointer'ý repository'de saklandýðý için siliþ repository'ye aittir.
}

void GameStateManager::startNewGame(QString categoryName) {
    // 1. Köprü: QString -> std::string dönüþümü
    m_wordManager->startNewGame(categoryName.toStdString()); 
    
    Word* selectedWord = m_wordManager->getCurrentWord();
    
    if (selectedWord == nullptr) {
        qDebug() << "Hata: WordManager kelime secemedi.";
        return;
    }

    // 2. Yeni oyun durumu oluþtur (180 saniye süre sýnýrý)
    m_currentGameState = new GameState(selectedWord, 180); 
    m_currentGameState->startTimer();
    
    // 3. Köprü: std::string -> QString (qDebug ekraný için)
    qDebug() << "Yeni oyun baslatildi. Kelime: " << QString::fromStdString(selectedWord->getWord());
}

void GameStateManager::makeGuess(QChar letter) {
    if (m_currentGameState == nullptr || m_currentGameState->isGameOver()) {
        qDebug() << "Aktif oyun yok veya oyun bitti.";
        return;
    }

    // 4. Köprü: QChar -> char 
    m_wordManager->makeGuess(letter.toLatin1()); 
    
    Word* currentWord = m_currentGameState->getCurrentWord();
    
    // WordManager içindeki haklarý kontrol et
    int remainingInManager = m_wordManager->getRemainingGuesses();
    
    // Eðer yanlýþ tahmin yapýldýysa GameState'deki hakký düþür
    if (remainingInManager < m_currentGameState->getRemainingGuesses()) {
         m_currentGameState->decreaseRemainingGuesses();
    }
    
    qDebug() << "Kalan hak: " << m_currentGameState->getRemainingGuesses();

    // Oyun bitiþ kontrolü
    if (m_currentGameState->isGameOver()) {
        m_currentGameState->endTimer();
        if (m_currentGameState->isGameWon()) {
            qDebug() << "TEBRIKLER, KAZANDINIZ!";
        } else {
            qDebug() << "KAYBETTINIZ. Kelime: " << QString::fromStdString(currentWord->getWord());
        }
    }
}

void GameStateManager::saveCurrentGame() {
    if (m_currentGameState && !m_currentGameState->isGameOver()) {
        m_currentGameState->endTimer();
        m_repository->saveGameState(m_currentGameState);
        qDebug() << "Oyun basariyla kaydedildi.";
    }
}

void GameStateManager::loadLastGame() {
    GameState* lastGame = m_repository->getLastGameState();
    if (lastGame) {
        m_currentGameState = lastGame;
        if (!m_currentGameState->isGameOver()) {
            m_currentGameState->startTimer();
        }
        qDebug() << "Son kayit yuklendi.";
    }
}

GameState* GameStateManager::getCurrentGameState() const {
    return m_currentGameState;
}
