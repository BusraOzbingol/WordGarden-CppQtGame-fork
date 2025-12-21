#include "PlayerRepository.h"

void PlayerRepository::addPlayer(Player* player) {
    players.append(player);
}

Player* PlayerRepository::getPlayerByName(const QString& name) {
    for (Player* player : players) {
        if (player->getName() == name)
            return player;
    }
    return nullptr;
}

QList<Player*> PlayerRepository::getAllPlayers() const {
    return players;
}