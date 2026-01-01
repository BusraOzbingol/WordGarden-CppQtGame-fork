/**
 * @file GameStateRepository.h
 * @brief Header file for the GameStateRepository class.
 * * Defines the storage mechanism for game sessions, allowing for saving 
 * and retrieving GameState objects.
 */

#ifndef GAMESTATEREPOSITORY_H
#define GAMESTATEREPOSITORY_H

#include "1_Entities/GameState.h"
#include <QList>


/**
 * @class GameStateRepository
 * @brief Manages a collection of GameState objects.
 * * This repository acts as a data store for game sessions, providing methods 
 * to persist the current state and retrieve historical game data.
 */
class GameStateRepository {
public:
    /**
	 * @brief Constructs a new GameStateRepository object.
     * * Initialized to manage an empty list of game states.
	  */
    GameStateRepository();

    /**
	  * @brief Adds a GameState to the repository.
	  * @param gameState Pointer to the GameState object to be stored.
	  */
    void saveGameState(GameState* gameState);
    
    /**
	  * @brief Retrieves the most recently added GameState.
	  * @return Pointer to the last GameState in the list, or nullptr if no states exist.
      */
    GameState* getLastGameState() const;
    
    /**
	 * @brief Retrieves all stored game states.
	 * @return A QList containing pointers to all GameState objects in the repository.
	  */
    QList<GameState*> getAllGameStates() const;

private:
    QList<GameState*> m_gameStates; ///< Internal list storing pointers to game sessions.
	};
};
#endif
