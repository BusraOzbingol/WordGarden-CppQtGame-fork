/**
 * @file GameStateRepository.h
 * @brief Implementation of the GameStateRepository class.
 * * This class handles the in-memory storage and retrieval of GameState objects.
 */

#include "2_Repository/GameStateRepository.h"
#include "1_Entities/GameState.h"
#include <QDebug>
#include <QList>

/**
 * @brief Default constructor for GameStateRepository.
 */
GameStateRepository::GameStateRepository() {
    // Constructor
}

/**
 * @brief Saves a game state by adding it to the internal list.
 * @param gameState Pointer to the GameState object to be saved.
 */
void GameStateRepository::saveGameState(GameState* gameState) {
    if (gameState != nullptr) {
        m_gameStates.append(gameState);
    }
}

/**
 * @brief Retrieves the most recently saved game state.
 * @return Pointer to the last GameState in the list, or nullptr if the list is empty.
 */
GameState* GameStateRepository::getLastGameState() const {
    if (m_gameStates.isEmpty()) {
        return nullptr;
    }
    return m_gameStates.last();
}

/**
 * @brief Retrieves all saved game states.
 * @return A QList containing pointers to all stored GameState objects.
 */
QList<GameState*> GameStateRepository::getAllGameStates() const {
    return m_gameStates;
}
