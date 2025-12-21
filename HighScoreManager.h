#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include "PlayerRepository.h"

class HighScoreManager {
private:
    PlayerRepository* repository;

public:
    HighScoreManager(PlayerRepository* repository);
    QList<Player*> getHighScores(int topN);
};

#endif // HIGHSCOREMANAGER_H