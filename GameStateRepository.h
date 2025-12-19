#ifndef GAMESTATEREPOSITORY_H
#define GAMESTATEREPOSITORY_H

#include "GameState.h"
#include <QList>

class GameStateRepository {
public:
    // Yapýcý metot (Eðer dosya yükleme gerekiyorsa burada yapýlýr)
    GameStateRepository();

    // Depolama Metotlarý
    void saveGameState(GameState* gameState);
    GameState* getLastGameState() const;
    QList<GameState*> getAllGameStates() const;

private:
    QList<GameState*> m_gameStates; // Kaydedilen oyun durumlarý listesi
};
#endif
