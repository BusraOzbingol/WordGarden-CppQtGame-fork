/**
 * @file GameStateManager.h
 * @brief Header file for the GameStateManager class.
 * * Manages the high-level logic of the game, coordinating data between 
 * repositories and the word management logic.
 */

#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "1_Entities/GameState.h"
#include "2_Repository/GameStateRepository.h"
#include "3_Manager/WordManager.h"
#include "1_Entities/Word.h"   
#include <QString>
#include <QChar>

/**
 * @class GameStateManager
 * @brief Orchestrates the game flow and state transitions.
 * * This class acts as a controller that handles starting new games, 
 * processing player guesses, and persisting game states via repositories.
 */
class GameStateManager {
public:
    /**
	     * @brief Constructor using Dependency Injection.
	     * @param repository Pointer to the repository for saving/loading states.
	     * @param wordManager Pointer to the manager handling word and scoring logic.
	     */
    GameStateManager(GameStateRepository* repository, WordManager* wordManager); 

    /**
	 * @brief Initiates a new game session with a random word from a category.
     * @param categoryName The name of the category (e.g., "Animals", "Plants").
	     */
    void startNewGame(QString categoryName);
    
    /** @brief Loads the most recently saved game state from the repository. */
    void loadLastGame();
    
    /**
     * @brief Handles the logic for a player's letter guess.
     * @param letter The character guessed by the player.
	     */
    void makeGuess(QChar letter);
    
    /** @brief Saves the current game session to the repository. */
    void saveCurrentGame();
    
   /**
    * @brief Gets the current active game state.
    * @return Pointer to the GameState object.
        */
    GameState* getCurrentGameState() const;
    
   /** @brief Destructor for cleaning up manager resources. */
    ~GameStateManager(); 
    
private:
    GameStateRepository* m_repository; ///< Repository for state persistence.
    WordManager* m_wordManager;      ///< Manager for word-related logic.
    GameState* m_currentGameState = nullptr;  ///< Pointer to the current active session.
    
    /** @brief Prevent copying to ensure single management of game resources. */
    GameStateManager(const GameStateManager&) = delete;
    
    /** @brief Prevent assignment to ensure single management of game resources. */
    GameStateManager& operator=(const GameStateManager&) = delete;
};

#endif // GAMESTATEMANAGER_H
