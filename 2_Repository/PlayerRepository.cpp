#include "2_Repository/PlayerRepository.h"

/**
 * @brief Adds a player to the repository.
 * @param player Pointer to the Player object to be added.
 * Player is added only if the pointer is not null.
 */
void PlayerRepository::addPlayer(Player* player) {
    if (player){
        players.append(player);
    }
}

/**
 * @brief Retrieves a player by matching their name.
 * @param name Name of the player to search for.
 * @return Pointer to the Player if found, otherwise nullptr.
 */
Player* PlayerRepository::getPlayerByName(const QString& name) {
    for (Player* player : players) {
        if (player->getName() == name)
            return player;
    }
    return nullptr;
}

/**
 * @brief Returns all players stored in the repository.
 * @return QList containing all Player pointers.
 */
QList<Player*> PlayerRepository::getAllPlayers() const {
    return players;
}

/**
 * @brief Deletes all stored Player objects and clears the list.
 * Uses qDeleteAll to free memory of all Player pointers.
 */
void PlayerRepository::clear(){
    qDeleteAll(players);
    players.clear();
}


