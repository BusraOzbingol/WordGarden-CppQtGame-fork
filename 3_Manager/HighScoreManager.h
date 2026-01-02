#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include "2_Repository/PlayerRepository.h"

/**
 * @class HighScoreManager
 * @brief Provides functionality for retrieving top-scoring players.
 */
class HighScoreManager {
private:
    PlayerRepository* repository;
    ///< Pointer to the PlayerRepository used for data access.

public:
    /**
     * @brief Constructs a HighScoreManager.
     * @param repository Pointer to a PlayerRepository instance.
     */
    HighScoreManager(PlayerRepository* repository);

    /**
     * @brief Retrieves the topN players with the highest scores.
     * @param topN Number of top players to return.
     * @return QList of Player pointers sorted by descending score.
     */
    QList<Player*> getHighScores(int topN);
};

#endif // HIGHSCOREMANAGER_H


