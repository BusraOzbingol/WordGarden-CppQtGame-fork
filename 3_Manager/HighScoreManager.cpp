#include "3_Manager/HighScoreManager.h"
#include <algorithm>

/**
 * @brief Constructs a HighScoreManager using an existing PlayerRepository.
 * @param repository Pointer to a PlayerRepository instance.
 */
HighScoreManager::HighScoreManager(PlayerRepository* repository)
    : repository(repository) {}

/**
 * @brief Retrieves the topN players sorted by highest score.
 * @param topN Number of highest-scoring players to return.
 * @return QList of Player pointers sorted in descending order by score.
 *
 * The function copies the list of all players, sorts them using std::sort and trims the list to the desired size.
 */
QList<Player*> HighScoreManager::getHighScores(int topN) {
    QList<Player*> players = repository->getAllPlayers();

    // Sort players
    std::sort(players.begin(), players.end(),
              [](Player* a, Player* b) {
                  return a->getScore() > b->getScore();
              });

    // Trims the list
    if (players.size() > topN)
        players = players.mid(0, topN);

    return players;
}


