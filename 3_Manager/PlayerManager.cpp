#include "3_Manager/PlayerManager.h"

/**
 * @brief Constructor for PlayerManager.
 * @param repository Pointer to the PlayerRepository instance.
 */
PlayerManager::PlayerManager(PlayerRepository* repository)
    : repository(repository) {}

/**
 * @brief Creates a new player and adds it to the repository.
 * @param name The name of the player to create.
 * @param level The level of the player (PlayerLevel enum value).
 * @return Player* Pointer to the newly created Player object.
 */
Player* PlayerManager::createPlayer(const QString& name, PlayerLevel level) {
    Player* player = new Player(name, level);
    repository->addPlayer(player);
    return player;
}

/**
 * @brief Retrieves a player by name.
 * @param name The name of the player to retrieve.
 * @return Player* Pointer to the Player if found, otherwise nullptr.
 */
Player* PlayerManager::getPlayer(const QString& name) {
    return repository->getPlayerByName(name);
}


