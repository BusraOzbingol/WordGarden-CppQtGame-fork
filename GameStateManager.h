#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "GameState.h"
#include "GameStateRepository.h"
#include "WordManager.h" 
#include "Word.h"        
#include <QString>
#include <QChar>

class GameStateManager {
public:
    // Dependency Injection: Gerekli baðýmlýlýklarý dýþarýdan alýr
    GameStateManager(GameStateRepository* repository, WordManager* wordManager); 

    // Oyun Akýþý Metotlarý
    void startNewGame(QString categoryName);
    void loadLastGame();
    void makeGuess(QChar letter);
    void saveCurrentGame();
    
    // Getter
    GameState* getCurrentGameState() const;
    
    // Yýkýcý metot: Bellek yönetimi için
    ~GameStateManager(); 
    
private:
    GameStateRepository* m_repository;
    WordManager* m_wordManager;      
    GameState* m_currentGameState = nullptr;
    
    // Kopyalamayý engelle (Güvenlik için)
    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;
};

#endif // GAMESTATEMANAGER_H
