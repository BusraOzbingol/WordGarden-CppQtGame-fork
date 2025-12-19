#include "GameStateRepository.h"
#include <QDebug>

GameStateRepository::GameStateRepository() {
    
}
void GameStateRepository::saveGameState(GameState* gameState) {
    if (gameState != nullptr) {
        // Yeni GameState nesnesini listeye ekle
        m_gameStates.append(gameState);
        
        // Burasý, Qt ile dosya I/O yapacaðýnýz yerdir. 
        // Örn: gameState'i JSON'a çevirip diske yazma (þimdilik simülasyon)
        qDebug() << "Oyun durumu baþarýyla kaydedildi. Toplam kayýt: " << m_gameStates.size();
    }
}
GameState* GameStateRepository::getLastGameState() const {
    if (m_gameStates.isEmpty()) {
        return nullptr; // Kayýtlý oyun durumu yok
    }
    
    // Listenin son elemaný en son kaydedilen durumdur
    return m_gameStates.last();
}
QList<GameState*> GameStateRepository::getAllGameStates() const {
    return m_gameStates;
}
