#include "HighScoreManager.h"
#include <algorithm>

HighScoreManager::HighScoreManager(PlayerRepository* repository)
    : repository(repository) {}

QList<Player*> HighScoreManager::getHighScores(int topN) {
    QList<Player*> players = repository->getAllPlayers();

    std::sort(players.begin(), players.end(),
              [](Player* a, Player* b) {
                  return a->getScore() > b->getScore();
              });

    if (players.size() > topN)
        players = players.mid(0, topN);

    return players;
}
