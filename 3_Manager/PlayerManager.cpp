#include "PlayerManager.h"

PlayerManager::PlayerManager(PlayerRepository* repository)
    : repository(repository) {}

Player* PlayerManager::createPlayer(const QString& name, PlayerLevel level) {
    Player* player = new Player(name, level);
    repository->addPlayer(player);
    return player;
}

Player* PlayerManager::getPlayer(const QString& name) {
    return repository->getPlayerByName(name);
}
