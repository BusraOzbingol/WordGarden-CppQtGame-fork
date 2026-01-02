#ifndef PLAYERREPOSITORY_H
#define PLAYERREPOSITORY_H

#include <QList>
#include "1_Entities/Player.h"

/**
 * @class PlayerRepository
 * @brief Stores and manages Player objects.
 *
 * This class provides basic repository operations such as adding players, retrieving players by name, retrieving all players, and clearing the list.
 */
class PlayerRepository {
private:
    QList<Player*> players;
    ///< Internal list storing pointers to Player objects.

public:
    /**
     * @brief Adds a new player to the repository.
     * @param player Pointer to the Player object to be added.
     */
    void addPlayer(Player* player);

    /**
     * @brief Searches for a player by name.
     * @param name The name of the player being searched for.
     * @return Pointer to the matching Player, or nullptr if not found.
     */
    Player* getPlayerByName(const QString& name);

    /**
     * @brief Retrieves all stored players.
     * @return QList containing pointers to all Player objects.
     */
    QList<Player*> getAllPlayers() const;

    /**
     * @brief Deletes all Player objects and clears the repository.
     * This function uses qDeleteAll to free memory for each Player pointer and then clears the internal list.
     */
    void clear();
};

#endif // PLAYERREPOSITORY_H


