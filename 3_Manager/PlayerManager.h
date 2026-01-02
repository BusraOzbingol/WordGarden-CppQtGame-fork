#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "2_Repository/PlayerRepository.h"

/**
 * @class PlayerManager
 * @brief Handles creation and retrieval of Player objects.
 */
class PlayerManager {
private:
    /**
     * @brief Pointer to the repository that stores all players.
     */
    PlayerRepository* repository;

public:
    /**
     * @brief Constructs a PlayerManager with the given repository.
     * @param repository Pointer to the PlayerRepository instance used for storing and retrieving players.
     */
    PlayerManager(PlayerRepository* repository);

    /**
     * @brief Creates a new player and adds it to the repository.
     * @param name Name of the player to create.
     * @param level Player level (enum PlayerLevel).
     * @return Player* Pointer to the newly created Player object.
     */
    Player* createPlayer(const QString& name, PlayerLevel level);

    /**
     * @brief Retrieves a player by their name.
     * @param name Name of the player to retrieve.
     * @return Player* Pointer to the Player if found, otherwise nullptr.
     */
    Player* getPlayer(const QString& name);
};

#endif // PLAYERMANAGER_H


